#include <peglib.h>
#include <QtCore>
#include <fstream>
#include <iterator>
#include <algorithm>

bool read_file(const char* path, std::vector<char>& buff)
{
 using namespace std;
    ifstream ifs(path, ios::in | ios::binary);
    if (ifs.fail()) {
        return false;
    }

    buff.resize(static_cast<unsigned int>(ifs.seekg(0, ios::end).tellg()));
    if (!buff.empty()) {
        ifs.seekg(0, ios::beg).read(&buff[0], static_cast<streamsize>(buff.size()));
    }
    return true;
}


int main(int a,char**b)
{
QCoreApplication app(a,b);
if (b[1]==NULL
	|| b[2]==NULL){
 std::cout <<"\n"<<b[0]<<" lddoutput dirtargetcopy\n";
 return 0;
}
QDir tgdirvalidornot(b[2]);
if (!tgdirvalidornot.exists()){
 std::cout <<"\n"<<b[2]<<" not valid target dir\n";
return 0;
}

using namespace peg;
std::string gram= R"(
OUTLDD <- DLL* / SPC*
DLL <- SPC FNAME SPC EQ SPC DLLNAME* SPC ADDR SPC 
	/ SPC FNAME SPC ADDR SPC
SPC <- [ \t\r\n]*
LN <- '\n'
EQ <- '=' '>'
FNAME <- [A-Z0-9a-z .+-/_]+
DLLNAME <- [A-Z0-9a-z .+-/_]+
ADDR <- '(' ADDRBASE ')'
ADDRBASE <- [0-9A-Fa-f Xx]+
)";
std::vector<char> lddout;
if (!read_file(b[1],lddout))
{
 std::cout <<"\nerror reading ldd output file "<<b[1]<<"\n";
return 0; 
}
parser p(gram.c_str());
 std::vector<std::string> dllnames;
std::vector<std::string> ignored={"libc.so","libpthread.so","libm.so","librt.so","libdl.so","libz.so"};
p["DLLNAME"]=[&dllnames,&ignored](const SemanticValues& sv){
	bool ign=false;
	for(decltype(ignored.size()) x=0;x<ignored.size();x++){
		QRegularExpression re(ignored.at(x).c_str(), QRegularExpression::CaseInsensitiveOption);
		QRegularExpressionMatch match = re.match(sv.str().c_str());
		if(match.hasMatch()){
			ign=true;
			std::cout <<"\nignoring dll: "<<sv.str();
		}
	}
	if(!ign){
		std::cout <<"\nfound dll name: "<<sv.str();
		dllnames.push_back(sv.str());
	}
};
if (p.parse(lddout.data())){

 for (decltype(dllnames.size())x=0;x<dllnames.size();x++){
 QFileInfo fn(dllnames.at(x).c_str());
 QString tgdir(b[2]);
 QString dirtarget=QDir::toNativeSeparators(tgdir);
 dirtarget.append("/");
 dirtarget.append(fn.fileName());
 std::cout <<"\n[+] copying "<<dllnames.at(x)<<" to "<<
 dirtarget.toUtf8().constData();
QString cmd="sh -c \"cp ";
cmd += QFile::encodeName(dllnames.at(x).c_str());
cmd += " ";
cmd += dirtarget;
cmd +=  "\"";
std::cout <<"\ncmd: "<<cmd.toUtf8().constData()<<"\n";
 int ret=QProcess::execute(cmd);
// auto ret= QFile::copy(QLatin1String(dllnames.at(x).c_str()),
//	dirtarget);
 QString gag("Failed with exit status error code : %1");
 std::string pret= ret==0 ? " Ok":gag.arg(ret).toUtf8().constData();
 std::cout << pret;
 }

}else{
 std::cout <<"\nparsing lddoutput failed.. :(";
}

std::cout <<"\n";
return 0;
}
