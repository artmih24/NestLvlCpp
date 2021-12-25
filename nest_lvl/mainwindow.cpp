#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <algorithm>
#include <QDebug>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
#include <sstream>
using namespace std;

int count_nest_lvl_of_for(QString file_){
    QFile input_file(file_);
    input_file.open(QIODevice::ReadOnly);
    QString source_code = "";
    QTextStream in(&input_file);
    int ind = 0, j = 0;
    while (!in.atEnd()){
        QString line = in.readLine();
        if ((ind = line.indexOf("//")) != -1)
            line.remove(ind, line.length() - ind);
        source_code += line + '\n';
    }
    input_file.close();
    QString sourcecode = "";
    bool inComment = false;
    bool inString = false;
    bool itIsChar = false;
    for (int i = 0; i < source_code.length() - 1; i++){
        sourcecode += " ";
        if (source_code.mid(i, 2) == "/*")
            inComment = true;
        if (source_code.mid(i, 2) == "*/")
            inComment = false;
        if (source_code[i] == '"')
            inString = !inString;
        if (source_code[i] == "'")
            itIsChar = !itIsChar;
        if ((itIsChar == false) && !(source_code[i] == "'")
                && (inString == false) && !(source_code[i] == '"')
                && (inComment == false) && (!(source_code[i] == '*' && source_code[i + 1] == '/') && (i > 0 && !(source_code[i - 1] == '*' && source_code[i] == '/'))))
            sourcecode += source_code[i];
    }
    QRegExp reg("[?!.,:\\s]");
    sourcecode.replace(reg, "");
    QList<QString> for_indexes;
    int in_brackets = 0;
    for (j = 0; j < sourcecode.length(); j++){
        if (j == sourcecode.indexOf("(", j))
            in_brackets++;
        if (j == sourcecode.indexOf(")", j))
            in_brackets--;
        if (j == sourcecode.indexOf("{", j))
            for_indexes << "{";
        if (j == sourcecode.indexOf("}", j))
            for_indexes << "}";
        if (j == sourcecode.indexOf(";", j))
            if (in_brackets == 0)
                for_indexes << ";";
        if ((j == sourcecode.indexOf(")for(", j)) || (j == sourcecode.indexOf(";for(", j)) || (j == sourcecode.indexOf("{for(", j)) || (j == sourcecode.indexOf("}for(", j)) || (j == sourcecode.indexOf(":for(", j)))
            for_indexes << "for";
    }
    int begin = for_indexes.indexOf("{");
    for (int i = 0; i <= begin; i++)
        for_indexes.removeFirst();
    if (!for_indexes.isEmpty())
        for_indexes.removeLast();
    int nest_lvl = 0;
    QList<int> max_nest_lvls, save_nest_lvls;
    for (int i = 0; i < for_indexes.length(); i++){
        if (for_indexes[i] == "for"){
            //if (brackets_flag == true)
            nest_lvl++;
        }
        if (for_indexes[i] == "{"){
            save_nest_lvls << nest_lvl;
        }
        if (for_indexes[i] == "}"){
            if (!save_nest_lvls.isEmpty()){
                nest_lvl = save_nest_lvls.last() - 1;
                save_nest_lvls.removeLast();
            }
            else
                nest_lvl = 0;
        }
        if (for_indexes[i] == ";"){
            max_nest_lvls << nest_lvl - 1;
            if (!save_nest_lvls.isEmpty())
                nest_lvl = save_nest_lvls.last();
            else
                nest_lvl = 0;
        }
    }
    /*QString nest_levels_str = "";
    for (int i = 0; i < max_nest_lvls.length(); i++)
        nest_levels_str += (QString::number(max_nest_lvls[i]) + ' ');
    qDebug() << nest_levels_str;*/
    std::sort(max_nest_lvls.begin(), max_nest_lvls.end());
    int max = (max_nest_lvls.last() > 0) ? max_nest_lvls.last() : 0;
    return max;
}

int count_nest_lvl_of_if_else(QString file_){
    QFile input_file(file_);
    input_file.open(QIODevice::ReadOnly);
    QString source_code = "";
    QTextStream in(&input_file);
    int ind = 0, j = 0;
    while (!in.atEnd()){
        QString line = in.readLine();
        if ((ind = line.indexOf("//")) != -1)
            line.remove(ind, line.length() - ind);
        source_code += line + '\n';
    }
    input_file.close();
    QString sourcecode = "";
    bool inComment = false;
    bool inString = false;
    bool itIsChar = false;
    for (int i = 0; i < source_code.length() - 1; i++){
        sourcecode += " ";
        if (source_code.mid(i, 2) == "/*")
            inComment = true;
        if (source_code.mid(i, 2) == "*/")
            inComment = false;
        if (source_code[i] == '"')
            inString = !inString;
        if (source_code[i] == "'")
            itIsChar = !itIsChar;
        if ((itIsChar == false) && !(source_code[i] == "'")
                && (inString == false) && !(source_code[i] == '"')
                && (inComment == false) && (!(source_code[i] == '*' && source_code[i + 1] == '/') && (i > 0 && !(source_code[i - 1] == '*' && source_code[i] == '/'))))
            sourcecode += source_code[i];
    }
    QRegExp reg("[?!.,:\\s]");
    sourcecode.replace(reg, "");
    qDebug() << sourcecode;
    QList<QString> if_else_indexes;
    int in_brackets = 0;
    for (j = 0; j < sourcecode.length(); j++){
        if (j == sourcecode.indexOf("(", j))
            in_brackets++;
        if (j == sourcecode.indexOf(")", j))
            in_brackets--;
        if (j == sourcecode.indexOf("{", j))
            if_else_indexes << "{";
        if (j == sourcecode.indexOf("}", j))
            if_else_indexes << "}";
        if (j == sourcecode.indexOf(";", j))
            if (in_brackets == 0)
                if_else_indexes << ";";
        if ((j == sourcecode.indexOf(";else", j)) || (j == sourcecode.indexOf("}else", j)))
            if_else_indexes << "else";
        if ((j == sourcecode.indexOf(")if(", j)) ||(j == sourcecode.indexOf(";if(", j)) || (j == sourcecode.indexOf("{if(", j)) || (j == sourcecode.indexOf("}if(", j))
                || (j == sourcecode.indexOf("}elseif(", j)) ||(j == sourcecode.indexOf(";elseif(", j)))
            if_else_indexes << "if";
    }
    int begin = if_else_indexes.indexOf("{");
    for (int i = 0; i <= begin; i++)
        if_else_indexes.removeFirst();
    if (!if_else_indexes.isEmpty())
        if_else_indexes.removeLast();
    QString if_else_str = "";
    for (int i = 0; i < if_else_indexes.length(); i++)
        if_else_str += (if_else_indexes[i] + ' ');
    qDebug() << if_else_str;
    int nest_lvl = 0;
    QList<int> max_nest_lvls, save_nest_lvls;
    int ii = 0;
    int brackets = 0;
    bool not_else = false;
    int not_else_i = 0;
    for (int i = 0; i < if_else_indexes.length(); i++){
        if (if_else_indexes[i] == "if"){
            ii = i;
            while (ii < if_else_indexes.length()){
                if (if_else_indexes[ii] == "{")
                    brackets++;
                if (if_else_indexes[ii] == "}")
                    brackets--;
                if (((if_else_indexes[ii] == "if") || (if_else_indexes[ii] == "else")) && (brackets == 0)){
                    not_else = (if_else_indexes[ii] == "if");
                    break;
                }
                if (ii < if_else_indexes.length())
                    ii++;
            }
            nest_lvl++;
            save_nest_lvls << nest_lvl;
            if (not_else == true){
                not_else_i++;
            }
        }
        if (if_else_indexes[i] == "else"){
            if (!save_nest_lvls.isEmpty()){
                nest_lvl = save_nest_lvls.last();
                save_nest_lvls.removeLast();
            }
            //nest_lvl++;
        }
        if (if_else_indexes[i] == "{"){
            save_nest_lvls << nest_lvl;
        }
        if (if_else_indexes[i] == "}"){
            if (!save_nest_lvls.isEmpty()){
                nest_lvl = save_nest_lvls.last();
                save_nest_lvls.removeLast();
            }
            else
                nest_lvl = 0;
        }
        if (if_else_indexes[i] == ";"){
            max_nest_lvls << nest_lvl - 1;
            while (not_else_i-- > nest_lvl)
                if (!save_nest_lvls.isEmpty())
                    save_nest_lvls.removeLast();
            if (!save_nest_lvls.isEmpty()){
                nest_lvl = save_nest_lvls.last();
            }
            else
                nest_lvl = 0;
        }
    }
    QString nest_levels_str = "";
    for (int i = 0; i < max_nest_lvls.length(); i++)
        nest_levels_str += (QString::number(max_nest_lvls[i]) + ' ');
    qDebug() << nest_levels_str;
    std::sort(max_nest_lvls.begin(), max_nest_lvls.end());
    return max_nest_lvls.last();
}

enum ttype_if_else
{
    tif,
    telse,
    tsemi,
    topen,
    tclose
};

int count_nest_lvl_of_if_else_2(QString file_){
    QFile input_file(file_);
    input_file.open(QIODevice::ReadOnly);
    QString source_code = "";
    QTextStream in(&input_file);
    int ind = 0, j = 0;
    while (!in.atEnd()){
        QString line = in.readLine();
        if ((ind = line.indexOf("//")) != -1)
            line.remove(ind, line.length() - ind);
        source_code += line + '\n';
    }
    input_file.close();
    QString sourcecode = "";
    bool inComment = false;
    bool inString = false;
    bool itIsChar = false;
    for (int i = 0; i < source_code.length() - 1; i++){
        //sourcecode += " ";
        if (source_code.mid(i, 2) == "/*")
            inComment = true;
        if (source_code.mid(i, 2) == "*/")
            inComment = false;
        if (source_code[i] == '"')
            inString = !inString;
        if (source_code[i] == "'")
            itIsChar = !itIsChar;
        if ((itIsChar == false) && !(source_code[i] == "'")
                && (inString == false) && !(source_code[i] == '"')
                && (inComment == false) && (!(source_code[i] == '*' && source_code[i + 1] == '/') && (i > 0 && !(source_code[i - 1] == '*' && source_code[i] == '/'))))
            sourcecode += source_code[i];
    }
    //qDebug() << sourcecode;
    string code = sourcecode.toStdString();
    istringstream fin(code);
    queue<ttype_if_else> toks;
    string token;
    char ch;
    while (fin.get(ch))
    {
        if (isalpha(ch))
            token += ch;
        if (!isalpha(ch))
        {
            if (token == "if")
                toks.push(ttype_if_else::tif);
            else if (token == "else")
                toks.push(ttype_if_else::telse);
            token = "";
        }
        if (ch == ';')
            toks.push(ttype_if_else::tsemi);
        if (ch == '{')
            toks.push(ttype_if_else::topen);
        if (ch == '}')
            toks.push(ttype_if_else::tclose);
    }
    ttype_if_else prev, curr = ttype_if_else::tsemi;
    stack<int> depth, secure;
    depth.push(-1);
    secure.push(1);
    int max = 0;
    while (!toks.empty()){
        prev = curr;
        curr = toks.front();
        toks.pop();

        switch (curr){
            case tif: // if
                if (prev == ttype_if_else::tsemi || prev == ttype_if_else::tclose){
                    while (depth.size() > abs(secure.top()))
                        depth.pop();
                }
                depth.push(depth.top() + 1);
                break;
            case topen: // {
                if (prev == ttype_if_else::telse)
                    secure.push(-static_cast<int>(depth.size()));
                else
                    secure.push(depth.size());
                break;
            case tclose: // }
                switch (prev){
                    case topen: case tclose: case tsemi:
                        while (depth.size() > abs(secure.top()))
                            depth.pop();
                        if (secure.top() < 0)
                            depth.pop();
                        secure.pop();
                        break;
                    default: throw runtime_error("closing nothing"); // if/else/other
                }
                break;
            case telse: // else
                break;
            case tsemi: // ;
                if (prev == ttype_if_else::telse){
                    //qDebug() << depth.top() << " ";
                    depth.pop();
                    continue;
                }
                if (prev == ttype_if_else::tsemi || prev == ttype_if_else::tclose){
                    while (depth.size() > abs(secure.top()))
                        depth.pop();
                }
                //qDebug() << depth.top() << " ";
                break;
            default:
                throw runtime_error("Unknown?!");
                break;
        }
        if (depth.top() > max)
            max = depth.top();
    }
    return max;
}

int count_nest_lvl_of_switch(QString file_){
    QFile input_file(file_);
    input_file.open(QIODevice::ReadOnly);
    QString source_code = "";
    QTextStream in(&input_file);
    int ind = 0, j = 0;
    while (!in.atEnd()){
        QString line = in.readLine();
        if ((ind = line.indexOf("//")) != -1)
            line.remove(ind, line.length() - ind);
        source_code += line + '\n';
    }
    input_file.close();
    QString sourcecode = "";
    bool inComment = false;
    bool inString = false;
    bool itIsChar = false;
    for (int i = 0; i < source_code.length() - 1; i++){
        sourcecode += " ";
        if (source_code.mid(i, 2) == "/*")
            inComment = true;
        if (source_code.mid(i, 2) == "*/")
            inComment = false;
        if (source_code[i] == '"')
            inString = !inString;
        if (source_code[i] == "'")
            itIsChar = !itIsChar;
        if ((itIsChar == false) && !(source_code[i] == "'")
                && (inString == false) && !(source_code[i] == '"')
                && (inComment == false) && (!(source_code[i] == '*' && source_code[i + 1] == '/') && (i > 0 && !(source_code[i - 1] == '*' && source_code[i] == '/'))))
            sourcecode += source_code[i];
    }
    QRegExp reg("[?!.,:\\s]");
    sourcecode.replace(reg, "");
    QList<QString> switch_indexes;
    int in_brackets = 0;
    for (j = 0; j < sourcecode.length(); j++){
        if (j == sourcecode.indexOf("(", j))
            in_brackets++;
        if (j == sourcecode.indexOf(")", j))
            in_brackets--;
        if (j == sourcecode.indexOf("{", j))
            switch_indexes << "{";
        if (j == sourcecode.indexOf("}", j))
            switch_indexes << "}";
        if (j == sourcecode.indexOf(";", j))
            if (in_brackets == 0)
                switch_indexes << ";";
        if ((j == sourcecode.indexOf(";switch(", j)) || (j == sourcecode.indexOf("{switch(", j)) || (j == sourcecode.indexOf("}switch(", j))
                || (j == sourcecode.indexOf(")switch(", j)) || (j == sourcecode.indexOf(":switch(", j)))
            switch_indexes << "switch";
    }
    int begin = switch_indexes.indexOf("{");
    for (int i = 0; i <= begin; i++)
        switch_indexes.removeFirst();
    if (!switch_indexes.isEmpty())
        switch_indexes.removeLast();
    int nest_lvl = 0;
    QList<int> max_nest_lvls, save_nest_lvls;
    for (int i = 0; i < switch_indexes.length(); i++){
        if (switch_indexes[i] == "switch"){
            //if (brackets_flag == true)
            nest_lvl++;
        }
        if (switch_indexes[i] == "{"){
            save_nest_lvls << nest_lvl;
        }
        if (switch_indexes[i] == "}"){
            if (!save_nest_lvls.isEmpty()){
                nest_lvl = save_nest_lvls.last();
                save_nest_lvls.removeLast();
            }
            else
                nest_lvl = 0;
        }
        if (switch_indexes[i] == ";"){
            max_nest_lvls << nest_lvl - 1;
            if (!save_nest_lvls.isEmpty())
                nest_lvl = save_nest_lvls.last();
            else
                nest_lvl = 0;
        }
    }
    std::sort(max_nest_lvls.begin(), max_nest_lvls.end());
    int max = (max_nest_lvls.last() > 0) ? max_nest_lvls.last() : 0;
    return max;
}

QList<int> count_nest_lvl_of_while_do_while(QString file_){
    QFile input_file(file_);
    input_file.open(QIODevice::ReadOnly);
    QString source_code = "";
    QTextStream in(&input_file);
    int ind = 0, j = 0;
    while (!in.atEnd()){
        QString line = in.readLine();
        if ((ind = line.indexOf("//")) != -1)
            line.remove(ind, line.length() - ind);
        source_code += line + '\n';
    }
    input_file.close();
    QString sourcecode = "";
    bool inComment = false;
    bool inString = false;
    bool itIsChar = false;
    for (int i = 0; i < source_code.length() - 1; i++){
        sourcecode += " ";
        if (source_code.mid(i, 2) == "/*")
            inComment = true;
        if (source_code.mid(i, 2) == "*/")
            inComment = false;
        if (source_code[i] == '"')
            inString = !inString;
        if (source_code[i] == "'")
            itIsChar = !itIsChar;
        if ((itIsChar == false) && !(source_code[i] == "'")
                && (inString == false) && !(source_code[i] == '"')
                && (inComment == false) && (!(source_code[i] == '*' && source_code[i + 1] == '/') && (i > 0 && !(source_code[i - 1] == '*' && source_code[i] == '/'))))
            sourcecode += source_code[i];
    }
    QRegExp reg("[?!.,:\\s]");
    sourcecode.replace(reg, "");
    QList<QString> while_indexes;
    int in_brackets = 0;
    for (j = 0; j < sourcecode.length(); j++){
        if (j == sourcecode.indexOf("(", j))
            in_brackets++;
        if (j == sourcecode.indexOf(")", j))
            in_brackets--;
        if (j == sourcecode.indexOf("{", j))
            while_indexes << "{";
        if (j == sourcecode.indexOf("}", j))
            while_indexes << "}";
        if (j == sourcecode.indexOf(";", j))
            if (in_brackets == 0)
                while_indexes << ";";
        if ((j == sourcecode.indexOf(")while(", j)) || (j == sourcecode.indexOf(";while(", j)) || (j == sourcecode.indexOf("{while(", j)) || (j == sourcecode.indexOf("}while(", j)))
            while_indexes << "while";
        if ((j == sourcecode.indexOf(")do", j)) || (j == sourcecode.indexOf(";do", j)) || (j == sourcecode.indexOf("{do", j)) || (j == sourcecode.indexOf("}do", j)))
            while_indexes << "do";
    }
    int begin = while_indexes.indexOf("{");
    for (int i = 0; i <= begin; i++)
        while_indexes.removeFirst();
    if (!while_indexes.isEmpty())
        while_indexes.removeLast();
    int nest_lvl = 0;
    int nest_lvl_while = 0;
    int nest_lvl_do_while = 0;
    bool itIsDoWhile = false;
    QList<QString> while_do_while;
    QList<int> max_nest_lvls_while, save_nest_lvls_while, max_nest_lvls_do_while, save_nest_lvls_do_while;
    for (int i = 0; i < while_indexes.length(); i++){
        if (while_indexes[i] == "while"){
            //itIsDoWhile = false;
            //nest_lvl_while++;
            if (!while_do_while.isEmpty()){
                /*if (while_do_while.last() == "while"){
                    itIsDoWhile = false;
                    nest_lvl_while++;
                }
                else if (while_do_while.last() == "do-while"){
                    itIsDoWhile = true;
                    nest_lvl_do_while++;
                }*/
            }
            else
                if (itIsDoWhile == false)
                    nest_lvl_while++;
        }
        if (while_indexes[i] == "do"){
            itIsDoWhile = true;
            nest_lvl_do_while++;
        }
        if (while_indexes[i] == "{"){
            if (itIsDoWhile == false){
                while_do_while << "while";
                save_nest_lvls_while << nest_lvl_while;
            }
            else{
                while_do_while << "do-while";
                save_nest_lvls_do_while << nest_lvl_do_while;
            }
        }
        if (while_indexes[i] == "}"){
            if (!while_do_while.isEmpty() && !save_nest_lvls_while.isEmpty() && !save_nest_lvls_do_while.isEmpty()){
                /*if (while_do_while.last() == "while"){
                    itIsDoWhile = false;
                    if (!save_nest_lvls_while.isEmpty()){
                        //nest_lvl_while = save_nest_lvls_while.last();
                        //save_nest_lvls_while.removeLast();
                    }
                }
                else if (while_do_while.last() == "do-while"){
                    itIsDoWhile = true;
                    if (!save_nest_lvls_do_while.isEmpty()){
                        //nest_lvl_do_while = save_nest_lvls_do_while.last();
                        //save_nest_lvls_do_while.removeLast();
                    }
                }*/
                if (!while_do_while.isEmpty())
                    //while_do_while.removeLast();
                    continue;
            }
            else{
                if (itIsDoWhile == false)
                    nest_lvl_while = 0;
                else
                    nest_lvl_do_while = 0;
            }
        }
        if (while_indexes[i] == ";"){
            if (!while_do_while.isEmpty() && !save_nest_lvls_while.isEmpty() && !save_nest_lvls_do_while.isEmpty()){
                if (while_do_while.last() == "while"){
                    itIsDoWhile = false;
                    if (!save_nest_lvls_while.isEmpty())
                        //nest_lvl_while = save_nest_lvls_while.last();
                        continue;
                }
                else if (while_do_while.last() == "do-while"){
                    itIsDoWhile = true;
                    if (!save_nest_lvls_do_while.isEmpty())
                        //nest_lvl_do_while = save_nest_lvls_do_while.last();
                        continue;
                }
            }
            else{
                if (itIsDoWhile == false)
                    nest_lvl_while = 0;
                else
                    nest_lvl_do_while = 0;
            }
        }
    }
    std::sort(max_nest_lvls_while.begin(), max_nest_lvls_while.end());
    std::sort(max_nest_lvls_do_while.begin(), max_nest_lvls_do_while.end());
    return {max_nest_lvls_while.last(), max_nest_lvls_do_while.last()};
}

enum ttype_while
{
    twhile,
    tdo,
    tend,
    topenb,
    tcloseb
};

int count_nest_lvl_of_while_2(QString file_){
    QFile input_file(file_);
    input_file.open(QIODevice::ReadOnly);
    QString source_code = "";
    QTextStream in(&input_file);
    int ind = 0, j = 0;
    while (!in.atEnd()){
        QString line = in.readLine();
        if ((ind = line.indexOf("//")) != -1)
            line.remove(ind, line.length() - ind);
        source_code += line + '\n';
    }
    input_file.close();
    QString sourcecode = "";
    bool inComment = false;
    bool inString = false;
    bool itIsChar = false;
    for (int i = 0; i < source_code.length() - 1; i++){
        //sourcecode += " ";
        if (source_code.mid(i, 2) == "/*")
            inComment = true;
        if (source_code.mid(i, 2) == "*/")
            inComment = false;
        if (source_code[i] == '"')
            inString = !inString;
        if (source_code[i] == "'")
            itIsChar = !itIsChar;
        if ((itIsChar == false) && !(source_code[i] == "'")
                && (inString == false) && !(source_code[i] == '"')
                && (inComment == false) && (!(source_code[i] == '*' && source_code[i + 1] == '/') && (i > 0 && !(source_code[i - 1] == '*' && source_code[i] == '/'))))
            sourcecode += source_code[i];
    }
    qDebug() << sourcecode;
    string code = sourcecode.toStdString();
    istringstream fin(code);
    queue<ttype_while> toks;
    string token;
    char ch;
    while (fin.get(ch))
    {
        if (isalpha(ch))
            token += ch;
        if (!isalpha(ch))
        {
            if (token == "while")
                toks.push(ttype_while::twhile);
            else if (token == "do")
                toks.push(ttype_while::tdo);
            token = "";
        }
        if (ch == ';')
            toks.push(ttype_while::tend);
        if (ch == '{')
            toks.push(ttype_while::topenb);
        if (ch == '}')
            toks.push(ttype_while::tcloseb);
    }
    ttype_while prev, curr = ttype_while::tend;
    stack<int> depth, secure;
    depth.push(-1);
    secure.push(1);
    int max = 0;
    while (!toks.empty()){
        prev = curr;
        curr = toks.front();
        toks.pop();

        switch (curr){
            case twhile: // while
                if (prev == ttype_while::tend || prev == ttype_while::tcloseb){
                    while (depth.size() > abs(secure.top()))
                        depth.pop();
                }
                depth.push(depth.top() + 1);
                break;
            /*case tif: // if
                if (prev == ttype_while::tsemi || prev == ttype_while::tclose){
                    while (depth.size() > abs(secure.top()))
                        depth.pop();
                }
                depth.push(depth.top() + 1);
                break;*/
            case topenb: // {
                //if (prev == ttype_while::telse)
                    //secure.push(-static_cast<int>(depth.size()));
                //else
                    //secure.push(depth.size());
                //break;
            case tcloseb: // }
                switch (prev){
                    case topenb: case tcloseb: case tend:
                        while (depth.size() > abs(secure.top()))
                            depth.pop();
                        if (secure.top() < 0)
                            depth.pop();
                        secure.pop();
                        break;
                    default: throw runtime_error("closing nothing"); // if/else/other
                }
                break;
            /*case telse: // else
                break;*/
            case tend: // ;
                /*if (prev == ttype_while::telse){
                    //qDebug() << depth.top() << " ";
                    depth.pop();
                    continue;
                }
                if (prev == ttype_while::tsemi || prev == ttype_while::tclose){
                    while (depth.size() > abs(secure.top()))
                        depth.pop();
                }
                //qDebug() << depth.top() << " ";
                break;*/
            default:
                throw runtime_error("Unknown?!");
                break;
        }
        if (depth.top() > max)
            max = depth.top();
    }
    return max;
}

int count_nest_lvl_of_while(QString file_){
    QFile input_file(file_);
    input_file.open(QIODevice::ReadOnly);
    QString source_code = "";
    QTextStream in(&input_file);
    int ind = 0, j = 0;
    while (!in.atEnd()){
        QString line = in.readLine();
        if ((ind = line.indexOf("//")) != -1)
            line.remove(ind, line.length() - ind);
        source_code += line + '\n';
    }
    input_file.close();
    QString sourcecode = "";
    bool inComment = false;
    bool inString = false;
    bool itIsChar = false;
    for (int i = 0; i < source_code.length() - 1; i++){
        sourcecode += " ";
        if (source_code.mid(i, 2) == "/*")
            inComment = true;
        if (source_code.mid(i, 2) == "*/")
            inComment = false;
        if (source_code[i] == '"')
            inString = !inString;
        if (source_code[i] == "'")
            itIsChar = !itIsChar;
        if ((itIsChar == false) && !(source_code[i] == "'")
                && (inString == false) && !(source_code[i] == '"')
                && (inComment == false) && (!(source_code[i] == '*' && source_code[i + 1] == '/') && (i > 0 && !(source_code[i - 1] == '*' && source_code[i] == '/'))))
            sourcecode += source_code[i];
    }
    QRegExp reg("[?!.,:\\s]");
    sourcecode.replace(reg, "");
    QList<QString> while_indexes;
    int in_brackets = 0;
    for (j = 0; j < sourcecode.length(); j++){
        if (j == sourcecode.indexOf("(", j))
            in_brackets++;
        if (j == sourcecode.indexOf(")", j))
            in_brackets--;
        if (j == sourcecode.indexOf("{", j))
            while_indexes << "{";
        if (j == sourcecode.indexOf("}", j))
            while_indexes << "}";
        if (j == sourcecode.indexOf(";", j))
            if (in_brackets == 0)
                while_indexes << ";";
        if ((j == sourcecode.indexOf(")while(", j)) || (j == sourcecode.indexOf(";while(", j)) || (j == sourcecode.indexOf("{while(", j))
                || (j == sourcecode.indexOf("}while(", j)) || (j == sourcecode.indexOf(":while(", j)))
            while_indexes << "while";
    }
    int begin = while_indexes.indexOf("{");
    for (int i = 0; i <= begin; i++)
        while_indexes.removeFirst();
    if (!while_indexes.isEmpty())
        while_indexes.removeLast();
    /*QString while_str = "";
    for (int i = 0; i < while_indexes.length(); i++)
        while_str += (while_indexes[i] + ' ');
    qDebug() << while_str;*/
    int nest_lvl = 0;
    QList<int> max_nest_lvls, save_nest_lvls;
    for (int i = 0; i < while_indexes.length(); i++){
        if (while_indexes[i] == "while"){
            //if (brackets_flag == true)
            nest_lvl++;
        }
        if (while_indexes[i] == "{"){
            save_nest_lvls << nest_lvl;
        }
        if (while_indexes[i] == "}"){
            if (!save_nest_lvls.isEmpty()){
                nest_lvl = save_nest_lvls.last() - 1;
                save_nest_lvls.removeLast();
            }
            else
                nest_lvl = 0;
        }
        if (while_indexes[i] == ";"){
            max_nest_lvls << nest_lvl - 1;
            if (!save_nest_lvls.isEmpty())
                nest_lvl = save_nest_lvls.last();
            else
                nest_lvl = 0;
        }
    }
    /*QString nest_levels_str = "";
    for (int i = 0; i < max_nest_lvls.length(); i++)
        nest_levels_str += (QString::number(max_nest_lvls[i]) + ' ');
    qDebug() << nest_levels_str;*/
    std::sort(max_nest_lvls.begin(), max_nest_lvls.end());
    int max = (max_nest_lvls.last() > 0) ? max_nest_lvls.last() : 0;
    return max;
}

int count_nest_lvl_of_do_while(QString file_){
    QFile input_file(file_);
    input_file.open(QIODevice::ReadOnly);
    QString source_code = "";
    QTextStream in(&input_file);
    int ind = 0, j = 0;
    while (!in.atEnd()){
        QString line = in.readLine();
        if ((ind = line.indexOf("//")) != -1)
            line.remove(ind, line.length() - ind);
        source_code += line + '\n';
    }
    input_file.close();
    QString sourcecode = "";
    bool inComment = false;
    bool inString = false;
    bool itIsChar = false;
    for (int i = 0; i < source_code.length() - 1; i++){
        sourcecode += " ";
        if (source_code.mid(i, 2) == "/*")
            inComment = true;
        if (source_code.mid(i, 2) == "*/")
            inComment = false;
        if (source_code[i] == '"')
            inString = !inString;
        if (source_code[i] == "'")
            itIsChar = !itIsChar;
        if ((itIsChar == false) && !(source_code[i] == "'")
                && (inString == false) && !(source_code[i] == '"')
                && (inComment == false) && (!(source_code[i] == '*' && source_code[i + 1] == '/') && (i > 0 && !(source_code[i - 1] == '*' && source_code[i] == '/'))))
            sourcecode += source_code[i];
    }
    QRegExp reg("[?!.,:\\s]");
    sourcecode.replace(reg, "");
    QList<QString> do_while_indexes;
    int in_brackets = 0;
    for (j = 0; j < sourcecode.length(); j++){
        if (j == sourcecode.indexOf("(", j))
            in_brackets++;
        if (j == sourcecode.indexOf(")", j))
            in_brackets--;
        if (j == sourcecode.indexOf("{", j))
            do_while_indexes << "{";
        if (j == sourcecode.indexOf("}", j))
            do_while_indexes << "}";
        if (j == sourcecode.indexOf(";", j))
            if ((in_brackets == 0) && (sourcecode[j - 1] != ')'))
                do_while_indexes << ";";
        if ((j == sourcecode.indexOf(")do", j)) || (j == sourcecode.indexOf(";do", j)) || (j == sourcecode.indexOf("{do", j))
                || (j == sourcecode.indexOf("}do", j)) || (j == sourcecode.indexOf(":do", j)) || (j == sourcecode.indexOf("dodo", j)))
            do_while_indexes << "do";
    }
    int begin = do_while_indexes.indexOf("{");
    for (int i = 0; i <= begin; i++)
        do_while_indexes.removeFirst();
    if (!do_while_indexes.isEmpty())
        do_while_indexes.removeLast();
    /*QString do_while_str = "";
    for (int i = 0; i < do_while_indexes.length(); i++)
        do_while_str += (do_while_indexes[i] + ' ');
    qDebug() << do_while_str;*/
    int nest_lvl = 0;
    QList<int> max_nest_lvls, save_nest_lvls;
    for (int i = 0; i < do_while_indexes.length(); i++){
        if (do_while_indexes[i] == "do"){
            //if (brackets_flag == true)
            nest_lvl++;
        }
        if (do_while_indexes[i] == "{"){
            save_nest_lvls << nest_lvl;
        }
        if (do_while_indexes[i] == "}"){
            if (!save_nest_lvls.isEmpty()){
                nest_lvl = save_nest_lvls.last() - 1;
                save_nest_lvls.removeLast();
            }
            else
                nest_lvl = 0;
        }
        if (do_while_indexes[i] == ";"){
            max_nest_lvls << nest_lvl - 1;
            if (!save_nest_lvls.isEmpty())
                nest_lvl = save_nest_lvls.last();
            else
                nest_lvl = 0;
        }
    }
    /*QString nest_levels_str = "";
    for (int i = 0; i < max_nest_lvls.length(); i++)
        nest_levels_str += (QString::number(max_nest_lvls[i]) + ' ');
    qDebug() << nest_levels_str;*/
    std::sort(max_nest_lvls.begin(), max_nest_lvls.end());
    int max = (max_nest_lvls.last() > 0) ? max_nest_lvls.last() : 0;
    return max;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->setText("");
    ui->label_2->setText("");

    QString filepath_for = "source_for_1.cpp";
    QString filepath_if_else = "source_if_1.cpp";
    QString filepath_switch = "source_switch_1.cpp";
    QString filepath_while = "source_while_1.cpp";
    QString filepath_do_while = "source_do_while_1.cpp";
    int max_nest_lvl_of_for = count_nest_lvl_of_for(filepath_for);
    int max_nest_lvl_of_if_else = count_nest_lvl_of_if_else_2(filepath_if_else);
    int max_nest_lvl_of_switch = count_nest_lvl_of_switch(filepath_switch);
    int max_nest_lvl_of_while = count_nest_lvl_of_while(filepath_while);
    int max_nest_lvl_of_do_while = count_nest_lvl_of_do_while(filepath_do_while);
    ui->label_2->setText(ui->label_2->text() + "Max: " + QString::number(max_nest_lvl_of_switch) + '\n');

}

MainWindow::~MainWindow()
{
    delete ui;
}

