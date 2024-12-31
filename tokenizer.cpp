#include<bits/stdc++.h>

using namespace std;

enum class TokenType {
    Identifier,
    ReservedWord,
    DataType,
    Operator,
    Value,
    Boolean,
    Punctuation,
    Unknown
};

class Token {
public:
    TokenType type;
    string value;
    int line_no;

    Token(TokenType type, const string& value, int line_no) 
        : type(type), value(value), line_no(line_no) {}
};

class FileReader {
public:
    string file_name;

    FileReader(const string& file_name) : file_name(file_name) {}

    string readFile() {
        ifstream file(file_name);
        if (!file.is_open()) {
            cerr << "Error opening file: " << file_name << endl;
            exit(1);
        }

        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
};

class Tokenizer {
private:
    
    unordered_map<string, TokenType> reservedWords = {
        {"agar", TokenType::ReservedWord},      // If
        {"warna", TokenType::ReservedWord},     // Else
        {"dobara", TokenType::ReservedWord},    // Loop/while
        {"roko", TokenType::ReservedWord},      // Break
        {"wapas", TokenType::ReservedWord},     // Return
        {"mukarrar", TokenType::ReservedWord},  // Constant (const)
    };


    unordered_map<string, TokenType> dataTypes = {
        {"adad", TokenType::DataType},          // Number (int, float)
        {"lafz", TokenType::DataType},          // String
        {"boolean", TokenType::DataType},    // Bool
        {"nishan", TokenType::DataType},        // Character
        {"khaali", TokenType::DataType},        // Void
        {"fahrist", TokenType::DataType},       // array
        {"sancha", TokenType::DataType},        // Class
    };


    unordered_map<string, TokenType> operators = {
        {":=", TokenType::Operator},
        {"+", TokenType::Operator},
        {"-", TokenType::Operator},
        {"*", TokenType::Operator},
        {"**", TokenType::Operator},
        {"/", TokenType::Operator},
        {"%", TokenType::Operator},
        {"==", TokenType::Operator},
        {"!=", TokenType::Operator},
        {"<", TokenType::Operator},
        {"<=", TokenType::Operator},
        {">", TokenType::Operator},
        {">=", TokenType::Operator},
        {"&&", TokenType::Operator},
        {"||", TokenType::Operator},
        {"!", TokenType::Operator}
    };

    unordered_map<string, TokenType> booleanValues = {
        {"sahi", TokenType::Boolean},
        {"ghalat", TokenType::Boolean}
    };

    vector<Token> tokens;
    string code;
    int line_no;
    bool inString;

public:
    Tokenizer(const string& code) : code(code), line_no(1), inString(false) {}

    vector<Token> tokenize() {
        string currentToken;

        regex identifierRegex("^(?:H|He|Li|Be|B|C|N|O|F|Ne|Na|Mg|Al|Si|P|S|Cl|Ar)_\\d{1,2}$");

        for (size_t i = 0; i < code.size(); ++i) {
            char ch = code[i];

            // strings
            if (ch == '"' && !inString) {
                inString = true;
                currentToken.push_back(ch);
                continue;
            }
            if (ch == '"' && inString) {
                inString = false;
                currentToken.push_back(ch);
                tokens.push_back({TokenType::Value, currentToken, line_no});
                currentToken.clear();
                continue;
            }

            if (isspace(ch)) {
                if (ch == '\n') {
                    line_no++;
                }else if(inString){
                    currentToken.push_back(ch);
                }
                continue;
            }

            if (ch == ';') {
                if (!currentToken.empty()) {
                    tokens.push_back({TokenType::Unknown, currentToken, line_no});
                    currentToken.clear();
                }
                tokens.push_back({TokenType::Punctuation, string(1, ch), line_no});
                continue;
            }

            if (ch == '(' || ch == ')' || ch == '{' || ch == '}') {
                if (!currentToken.empty()) {
                    tokens.push_back({TokenType::Unknown, currentToken, line_no});
                    currentToken.clear();
                }
                tokens.push_back({TokenType::Punctuation, string(1, ch), line_no});
                continue;
            }

            if (isdigit(ch) && !inString) {
                currentToken.push_back(ch);
                while (i + 1 < code.size() && (isdigit(code[i + 1]) || code[i + 1] == '.')) {
                    currentToken.push_back(code[++i]);
                }
                if (regex_match(currentToken, identifierRegex)) {
                    tokens.push_back({TokenType::Identifier, currentToken, line_no});
                }else{
                    tokens.push_back({TokenType::Value, currentToken, line_no});
                }
                currentToken.clear();
                continue;
            }

            currentToken.push_back(ch);
            if (reservedWords.find(currentToken) != reservedWords.end()) {
                tokens.push_back({reservedWords[currentToken], currentToken, line_no});
                currentToken.clear();
                continue;
            }
            if (dataTypes.find(currentToken) != dataTypes.end()) {
                tokens.push_back({dataTypes[currentToken], currentToken, line_no});
                currentToken.clear();
                continue;
            }
            if (booleanValues.find(currentToken) != booleanValues.end()) {
                tokens.push_back({booleanValues[currentToken], currentToken, line_no});
                currentToken.clear();
                continue;
            }
            
            // fixed 2-char ops
            if (i + 1 < code.size()) {
                string twoCharOp = currentToken + code[i + 1];
                if (operators.find(twoCharOp) != operators.end()) {
                    tokens.push_back({operators[twoCharOp], twoCharOp, line_no});
                    currentToken.clear();
                    i++;
                    continue;
                }
            }

            if (operators.find(currentToken) != operators.end()) {
                tokens.push_back({operators[currentToken], currentToken, line_no});
                currentToken.clear();
                continue;
            }
        }

        return tokens;
    }
};

void printTokens(const vector<Token>& tokens) {
    for (const auto& token : tokens) {
        cout << "Line no: " << token.line_no << ", "
             << "Token: " << token.value << ", "
             << "Type: ";
        
        switch (token.type) {
            case TokenType::Identifier:
                cout << "Identifier";
                break;
            case TokenType::ReservedWord:
                cout << "Reserved Word";
                break;
            case TokenType::DataType:
                cout << "Data Type";
                break;
            case TokenType::Operator:
                cout << "Operator";
                break;
            case TokenType::Value:
                cout << "Value";
                break;
            case TokenType::Boolean:
                cout << "Boolean";
                break;
            case TokenType::Punctuation:
                cout << "Punctuation";
                break;
            case TokenType::Unknown:
                cout << "Unknown";
                break;
        }
        cout << endl;
    }
}

int main() {
    string file_name;

    cout << "Enter the file name (without extension): ";
    cin >> file_name;

    FileReader fileReader("./programs/" + file_name + ".oem");
    string code = fileReader.readFile();

    Tokenizer tokenizer(code);
    vector<Token> tokens = tokenizer.tokenize();

    printTokens(tokens);

    return 0;
}
