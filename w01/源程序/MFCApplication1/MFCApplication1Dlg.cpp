
// MFCApplication1Dlg.cpp: 实现文件

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, catFile);
	DDX_Control(pDX, IDC_EDIT2, codeFile);
	DDX_Control(pDX, IDC_EDIT3, inStr);
	DDX_Control(pDX, IDC_EDIT4, outStr);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}










const int keywordNum = 63;   // 63个关键字
const int operatorNum = 28;   // 28个运算符
const int delimiterNum = 17;   // 17个定界符

const int intNum = 109;   // 整数编号：109
const int doubleNum = 110;   // 浮点数编号：110
const int charNum = 111;   // 字符编号：111
const int stringNum = 112;   // 字符串编号：112
const int identifierNum = 113;   // 标识符编号：113
const int commentNum = 114;   // 注释编号：114

const string op = "+-*/%=!&|<>";

map<string, int> catMap;   // 编码表
string keywords[63];   // 关键字表
string operators[28];   // 运算符表
string delimiters[17];   // 定界符表

enum { _ID_, _INT_, _DB_, _OP_, _DEL_, _KW_, _CH_, _STR_, _COM_, _SP_ };
string cat[10] = { "identifier", "int", "double", "operator", "delimiter", "keyword", "char", "string", "comment", "space" };

const int _EOF_ = -2;
const int _ERROR_ = -1;

struct Token {
	string value;   // 记号的值
	string category;   // 记号的类型
	int number;   // 对应的编码
	Token() : value("#"), category("delimiter"), number(108) {}
	Token(string val, string cat, int num) : value(val), category(cat), number(num) {}
	friend ostream& operator<<(ostream& os, const Token& t) {
		os << "记号【" << t.value << "】类型【" << t.category << "】编码【" << t.number << "】；";
		return os;
	}
};

vector<Token> tokenList;  // 存储识别出的Token

// 读入文本文件
vector<string> ReadFile(string fileName) {
	vector<string> tmp;
	ifstream fin;
	fin.open(fileName, ios::in);
	string temp;
	while (getline(fin, temp)) { tmp.push_back(temp); }
	fin.close();
	return tmp;
}

// 读入catFile，初始化编码表catMap
int Init(string name) {
	ifstream fin(name, ios::in);
	if (!fin) return -1;
	fin.close();
	vector<string> tmp = ReadFile(name);
	if (tmp.size() > 0) {
		for (int i = 0; i < keywordNum; i++) {
			keywords[i] = tmp[i];
			catMap[tmp[i]] = i + 1;
		}
		for (int i = 0; i < operatorNum; i++) {
			operators[i] = tmp[i + keywordNum];
			catMap[tmp[i + keywordNum]] = i + keywordNum + 1;
		}
		for (int i = 0; i < delimiterNum; i++) {
			delimiters[i] = tmp[i + keywordNum + operatorNum];
			catMap[tmp[i + keywordNum + operatorNum]] = i + keywordNum + operatorNum + 1;
		}
	}
	return 1;
}


void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	// 获取catFile文件路径
	CString str;
	catFile.GetWindowTextW(str);

	// 根据catFile初始化编码表
	string path = (CStringA)str;
	int result = Init(path);
	if (result == -1) MessageBox(_T("路径无效"));
	else MessageBox(_T("初始化成功"));
}


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


int pos, len;  // 当前字符位置和长度
string codeStr, tempStr;  // 当前识别的字符串

// 读入原始代码文件，存入codeStr
void ReadOrg(string name) {
    vector<string> tmp = ReadFile(name);
    for (int i = 0; i < tmp.size(); i++) {
        codeStr += tmp[i] + '\r' + '\n';
    }
    len = codeStr.size();
}

// 查看当前位置的下一个字符
char FindNext() {
    return pos + 1 < len ? codeStr[pos + 1] : '\0';
}

// 判断数字
bool IsDigit(char c) {
    return c >= '0' && c <= '9';
}

// 判断字母
bool IsLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

//判断关键字
bool IsKeyword(string s) {
    for (int i = 0; i < keywordNum; i++) {
        if (s == keywords[i]) return true;
    }
    return false;
}

// 判断单个的运算符号
bool IsOp(char ch) {
    return op.find(ch) != string::npos;
}

// 判断运算符
bool IsOperator(string s) {
    for (int i = 0; i < operatorNum; i++) {
        if (s == operators[i]) return true;
    }
    return false;
}

// 判断定界符
bool IsDelimiter(char ch) {
    for (int i = 0; i < delimiterNum; i++) {
        if (ch == delimiters[i][0]) return true;
    }
    return false;
}

// 判断记号类型
int Judge(char ch) {
    // 空格、空行
    if (ch == '\n' || ch == ' ') return _SP_;

    // 数字
    if (IsDigit(ch)) {
        char nextChar = FindNext();
        // 0.xx类型的浮点数
        if (ch == '0' && nextChar == '.') {
            pos++;
            // .后面不是数字，错误
            if (!IsDigit(FindNext())) return _ERROR_;
            // .后面是数字
            tempStr = "0.";
            while (IsDigit(FindNext())) {
                tempStr += FindNext();
                pos++;
            }
            return _DB_;
        }
        // 整数0
        else if (ch == '0' && !IsDigit(nextChar)) {
            tempStr = "0";
            return _INT_;
        }
        // xx.xx\xx类型的不以0开头的数
        else if (ch != '0') {
            tempStr = ch;
            while (IsDigit(FindNext())) {
                tempStr += FindNext();
                pos++;
            }
            char nextChar = FindNext();
            // xx.xx类型的浮点数
            if (nextChar == '.') {
                tempStr += nextChar;
                pos++;
                nextChar = FindNext();
                if (IsDigit(nextChar)) {
                    tempStr += FindNext();
                    pos++;
                    while (IsDigit(FindNext())) {
                        tempStr += FindNext();
                        pos++;
                    }
                    return _DB_;
                }
                else return _ERROR_;
            }
            // xx类型的整数
            else return _INT_;
        }
        // 其他错误情况
        else {
            pos++;
            return _ERROR_;
        }
    }

    // 标识符、关键词
    if (IsLetter(ch)) {
        tempStr = ch;
        char nextChar = FindNext();
        while (IsLetter(nextChar) || IsDigit(nextChar)) {
            tempStr += nextChar;
            pos++;
            nextChar = FindNext();
        }
        return IsKeyword(tempStr) ? _KW_ : _ID_;
    }

    // 字符串
    if (ch == '\"') {
        // 压缩时读到字符串对应的编码后自动加上双引号
        //tokenList.push_back(Token("\"", cat[_DEL_], 95));
        tempStr = "";
        char nextChar = FindNext();
        while (nextChar != '\"') {
            tempStr += nextChar;
            pos++;
            nextChar = FindNext();
        }
        tokenList.push_back(Token(tempStr, cat[_STR_], stringNum));
        //tokenList.push_back(Token("\"", cat[_DEL_], 95));
        pos += 1;
        return _STR_;
    }

    // 字符
    if (ch == '\'') {
        tempStr = "";
        pos++;
        char nextChar = FindNext();
        // 单个非空字符
        if (nextChar == '\'') {
            // 压缩时读到字符对应的编码后自动加上单引号
            //tokenList.push_back(Token("'", cat[_DEL_], 94));
            tempStr += codeStr[pos];
            tokenList.push_back(Token(tempStr, cat[_CH_], charNum));
            //tokenList.push_back(Token("'", cat[_DEL_], 94));
            pos++;
            return _CH_;
        }
        // 空
        else if (codeStr[pos] == '\'') {
            //tokenList.push_back(Token("\'", cat[_DEL_], 94));
            tokenList.push_back(Token(tempStr, cat[_CH_], charNum));
            //tokenList.push_back(Token("\'", cat[_DEL_], 94));
            return _CH_;
        }
        //// 错误，不是char
        //else {
        //    while (pos < len && nextChar != '\'') {
        //        pos++;
        //        nextChar = FindNext();
        //    }
        //    pos++;
        //    return _ERROR_;
        //}
    }

    // 注释
    if (ch == '/') {
        // 不保留注释，判断后不进行存储
        // /*xxx*/类型的块注释
        if (FindNext() == '*') {
            pos++;
            char nextChar = FindNext();
            pos++;
            //tempStr = "";
            while (pos < len) {
                if (nextChar == '*' && FindNext() == '/') {
                    //tokenList.push_back(Token("/*", cat[_DEL_], 96));
                    //tokenList.push_back(Token(tempStr, cat[_COM_], commentNum));
                    //tokenList.push_back(Token("*/", cat[_DEL_], 97));
                    pos += 2;
                    return _COM_;
                }
                // 记录（忽略）注释内容
                else {
                    //tempStr += nextChar;
                    nextChar = FindNext();
                    pos++;
                }
            }
            return _ERROR_;
        }
        // //xxx类型的单行注释
        if (FindNext() == '/') {
            pos++;
            char nextChar = FindNext();
            pos++;
            //tempStr = "";
            while (pos < len) {
                if (nextChar == '\n') {
                    //tokenList.push_back(Token("//", cat[_DEL_], 98));
                    //tokenList.push_back(Token(tempStr, cat[_COM_], commentNum));
                    return _COM_;
                }
                else {
                    //tempStr += nextChar;
                    nextChar = FindNext();
                    pos++;
                }
            }
        }
    }

    // 运算符
    if (IsOp(ch)) {
        tempStr = "";
        tempStr += ch;
        char nextChar = FindNext();
        if (IsOp(nextChar)) {
            if (IsOperator(tempStr + nextChar)) {
                tempStr += nextChar;
                pos++;
            }
        }
        return _OP_;
    }

    // 定界符
    if (IsDelimiter(ch)) {
        tempStr = "";
        tempStr += ch;
        return _DEL_;
    }

    // 其它错误情况
    return _ERROR_;
}

int ReadNext() {
    int num = Judge(codeStr[pos]);

    // 跳过空格空行
    while (pos < len && num == _SP_) {
        pos++;
        num = Judge(codeStr[pos]);
    }

    // 已经读到最后
    if (pos >= len) return _EOF_;

    pos++;
    // 处理刚刚的判断
    if (num == _ERROR_) return _ERROR_;
    if (num == _DB_) {
        tokenList.push_back(Token(tempStr, cat[_DB_], doubleNum));
        return _DB_;
    }
    if (num == _INT_) {
        tokenList.push_back(Token(tempStr, cat[_INT_], intNum));
        return _INT_;
    }
    if (num == _ID_) {
        tokenList.push_back(Token(tempStr, cat[_ID_], identifierNum));
        return _ID_;
    }
    if (num == _OP_ || num == _KW_ || num == _DEL_) {
        tokenList.push_back(Token(tempStr, cat[num], catMap[tempStr]));
        return num;
    }
    return 0;
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	// 获取原始文件路径
	CString codePath;
	codeFile.GetWindowTextW(codePath);

	// 显示原始文件内容
    string name = (CStringA)codePath;
    codeStr = ""; ReadOrg(name);
    CString instr(codeStr.c_str());
	inStr.SetWindowTextW(instr);

    // 词法分析，处理程序
    while (pos < len) {  
        int flag = ReadNext();
        if (flag == _EOF_) break;
    }
    // 输出压缩文件（二进制）
    string zipPath = (CStringA)codePath;
    zipPath = zipPath.erase(zipPath.size() - 3) + "dat";
    ofstream writeZip(zipPath, ios::out | ios::binary);
    char n;
    for (auto t : tokenList) {
        n = (char)t.number;
        if (t.category == "keyword" || t.category == "operator" || t.category == "delimiter")
            writeZip.write((char*)&n, 1);   // 写入编码，1字节
        if (t.category == "int" || t.category == "double"
            || t.category == "char" || t.category == "string" || t.category == "identifier") {
            writeZip.write((char*)&n, 1);   // 写入编码，1字节
            int num = t.value.size();
            n = (char)num;
            writeZip.write((char*)&n, 1);   // 写入长度，1字节
            for (int i = 0; i < num; i++) {
                n = t.value[i];
                writeZip.write((char*)&n, 1);   // 逐个写入，总共长度个字节
            }
        }
    }
    writeZip.close();
    // 浏览压缩文件（二进制）
    int x; string tmp = "";
    ifstream readZip(zipPath, ios::in | ios::binary);
    while (!readZip.eof()) {
        readZip.read((char*)&n, 1);
        x = (int)n;
        if (x > 1 && x <= 108) tmp += to_string(x);
        else {
            readZip.read((char*)&n, 1);
            x = (int)n;
            tmp += to_string(x);
            for (int i = 0; i < x; i++) {
                readZip.read((char*)&n, 1);
                tmp += n;
            }
        }
    }
    readZip.close();
    CString outstr(tmp.c_str());
    outStr.SetWindowTextW(outstr);

}

// D:\C++project\编译原理1\编译原理1\category.txt

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	// 获取压缩文件路径
	CString codePath;
	codeFile.GetWindowTextW(codePath);

	// 显示压缩后文件内容
    string name = (CStringA)codePath;
    string zipStr = "";
    char n; int x;
    ifstream readZip(name, ios::in | ios::binary);
    while (!readZip.eof()) {
        readZip.read((char*)&n, 1);
        x = (int)n;
        if (x > 1 && x <= 108) zipStr += to_string(x);
        else {
            readZip.read((char*)&n, 1);
            x = (int)n;
            zipStr += to_string(x);
            for (int i = 0; i < x; i++) {
                readZip.read((char*)&n, 1);
                zipStr += n;
            }
        }
    }
    readZip.close();
    CString instr(zipStr.c_str());
    inStr.SetWindowTextW(instr);

    // 将压缩文件解压成cpp文件，并浏览解压结果
    int last = 114;
    string unzFile = name;
    unzFile = unzFile.erase(unzFile.size() - 3) + "cpp";
    string unzStr = "";
    ofstream writeUnz;
    writeUnz.open(unzFile, ios::out);
    ifstream readZip_(name, ios::in | ios::binary);
    while (!readZip_.eof()) {
        readZip_.read((char*)&n, 1);
        x = (int)n;
        if ((last <= 63 || last == 113) && (x <= 63 || x == 113)) {
            writeUnz << ' ';
            unzStr += ' ';
        }
        last = x;
        if (x > 1 && x <= 63) {
            writeUnz << keywords[x - 1];
            unzStr += keywords[x - 1];
        }
        else if (x > 63 && x <= 91) {
            writeUnz << operators[x - 64];
            unzStr += operators[x - 64];
        }
        else if (x > 91 && x <= 108) {
            writeUnz << delimiters[x - 92];
            unzStr += delimiters[x - 92];
        }
        else {
            readZip_.read((char*)&n, 1);
            x = (int)n;
            for (int i = 0; i < x; i++) {
                readZip_.read((char*)&n, 1);
                writeUnz << n;
                unzStr += n;
            }
        }
    }
    readZip_.close();
    writeUnz.close();
    CString outstr(unzStr.c_str());
    outStr.SetWindowTextW(outstr);
}
