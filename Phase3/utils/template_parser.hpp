#ifndef TEMPLATE_PARSER_HPP_INCLUDE
#define TEMPLATE_PARSER_HPP_INCLUDE

#include <cstring>
#include <iostream>
#include <map>
#include <string>

#include "../server/server.hpp"
#include "request.hpp"
#include "utilities.hpp"

namespace SysCmd {
#ifdef _WIN32
const std::string rm = "del ";
const std::string programStart = "";
const std::string mkdir = "mkdir ";
const std::string slash = "\\";
const std::string fileExtention = ".exe";
#else
const std::string rm = "rm -f ";
const std::string programStart = "./";
const std::string mkdir = "mkdir ";
const std::string slash = "/";
const std::string fileExtention = ".o";
#endif
} // namespace SysCmd

const std::string beginCodeBlockTag = "<%";
const std::string endCodeBlockTag = "%>";
const std::string utilitiesHeaderPath = "utils/utilities.hpp";
const std::string utilitiesPath = "utils/utilities.cpp";
const std::string strutilsHeaderPath = "utils/strutils.hpp";
const std::string strutilsPath = "utils/strutils.cpp";
const std::string cc = "g++ -std=c++11 -Wall -pedantic";
const std::string compileDirectory = "templateCompile";
const std::string toCompileFile = "compiled.cpp";
const std::string staticTemplate = "staticTemplate.html";
const std::string outputFolder = ".template";
const std::string mapFile = "map.txt";
const std::string localTemplate(const int parserNum);

class TemplateParser {
public:
    TemplateParser(std::string _filePath);
    ~TemplateParser();

    std::string getHtml(std::map<std::string, std::string> _context);

private:
    class TemplateUtils {
    public:
        static void runSystemCommand(std::string command, std::string errorMessage);
        static int writeMapToFile(std::string fname,
                                  std::map<std::string, std::string>* m);
    };

    static int lastParserNum;
    int parserNum;
    std::string filePath;
    std::string code;
    std::map<std::string, std::string> context;
    int variableCount;
    std::string html;
    std::string programName;

    void parseTemplate();
    int findBeginOfCodeBlock(int startPosition, std::string& unparsedTemplate);
    int findEndOfCodeBlock(int startPosition, std::string& unparsedTemplate);
    void appendHTMLToCode(int begin, int end, std::string const& html);
    void appendCodeBlockToCode(int begin, int end, std::string& unparsedTemplate);
    void generateCode();
    void addIncludesToCode();
    void addReadFromTemplateToCode();
    void addReturnToCode();
    void addContextMapToCode();
    std::string runGeneratedCode();
    void makeExecutableTemplate();
    void makeLocalTemplate();
    void compileCode();
    void deleteExecutable();
    void deleteLocalTemplate();
};

#endif // TEMPLATE_PARSER_HPP_INCLUDE
