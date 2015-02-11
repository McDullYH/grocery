/*
   this test file is very important ,it shows many of c and c++ traps
 */



#include <pwd.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>

#define OPEN_LOG
#define LOG_DETAIL
#define LOG_ERROR
#define LOG_INFO
#define LOG_DEBUG
#define LOG_WARN
#include "log.h"

using namespace std;

#define SLASH '/'


//#include <head1.h>
//#include <head2.h>

#define MAX_PATH 256



#ifdef SPARC64
#define FOURCC(a,b,c,d) \
    ( ((uint32_t)d) | ( ((uint32_t)c) << 8 ) | ( ((uint32_t)b) << 16 ) | ( ((uint32_t)a) << 24 ) )
#else
#define FOURCC(a,b,c,d) \
    ( ((uint32_t)a) | ( ((uint32_t)b) << 8 ) | ( ((uint32_t)c) << 16 ) | ( ((uint32_t)d) << 24 ) )
#endif


#define testNull(p)                                           \
{                                                      \
  if(p==0)                                            \
  printf("ret is NULL at line %d\r\n",__LINE__);          \
  return false;                                       \
}

#define PRINTSTR(STR)                                           \
{                                                               \
  printf(#STR"  is %s\r\n",STR);                                 \
}                                                               

#define LINK(X)                       \
    int var##X=0;                         \
int X##var=0;


#define myPrintf(info,fmt,...)  \
{                               \
  printf("%s",info);          \
  printf(fmt,__VA_ARGS__);    \
}



class Base
{
 public:
  virtual void printMyself()=0;
  Base(){data=0;};
 protected:
  int data;
};


class A:public Base
{
 public:
  A()
  {
    printf("A create!\r\n");
  }
  virtual void printMyself()
  {
    printf("i am a sample of A! data is %d\r\n",data);
  }
  virtual ~A()
  {
    printf("A destroy!\r\n");
  }
};


struct S
{
  int c;
  double m;
  int a;
  int b;
};

class RunTime
{
 public:
  RunTime(const char* fn,double &d):data(d)
  {
    startTime=clock();
    strcpy(funcName,fn);
  }
  virtual ~RunTime()
  {
    endTime=clock();
    data=((double)(endTime-startTime))/CLOCKS_PER_SEC;
    printf("function %s run %f time\r\n",funcName,data);
  }
 private:
  clock_t startTime;
  clock_t endTime;
  double &data;
  char funcName[100];
  //function name do not longer than 99!
};

void current_dir();
void print_sizes();
void test_endian();
void get_user_dir();
void findAllFile(char * pFilePath);
bool mkdirRescure();
bool file_fget_test();
bool file_IO();
bool clock_test();
bool get_file_size(const char*);
bool malloc_test();
bool malloc_test2();
bool test_switch();
bool test_printf();
bool test_fwrite();
bool test_plusplusPoint();
bool test_random(int,int);
bool test_while();
void IOTest();
void CPUTest();
void signed_and_unsigned();
void argTest(int64_t);
int test_getpwnam();



long UOFCreateDirectory(const char *dirUrl);
char* getDirDir(const char* dirUrl);


int main(int argc,char* argv[])
{


  test_getpwnam();

  //printf("%02d\n", 3);

  //LOGE("color\r\n");
  //LOGW("color\r\n");
  //LOGI("color\r\n");
  //LOGD("color\r\n");

  //int a=100;
  //double b =30.0;
  //LOGX(a);
  //LOGX(b);


  //printf("%d\r\n",access("/home/yaohao/test/",W_OK));


  //printf("/home/yaohao/ne return %ld\r\n",UOFCreateDirectory("/home/yaohao/ne"));
  //printf("/home/yaohao/e return %ld\r\n",UOFCreateDirectory("/home/yaohao/e"));
  //printf("/home/yaohao/ena/ena return %ld\r\n",UOFCreateDirectory("/home/yaohao/ena/ena"));
  //printf("/root/ne return %ld\r\n",UOFCreateDirectory("/root/ne return"));
  //printf("/home/yaohao/1/2/3/4/5/6/7/8/9 return %ld\r\n",UOFCreateDirectory("/home/yaohao/1/2/3/4/5/6/7/8/9"));

  //uint64_t d=  -100;
  //argTest(d);


  //IOTest();
  //CPUTest();


  //get_file_size("/home/yaohao/test/file/");
  //get_file_size("/home/yaohao/test/");
  //printf("%d\r\n",access("/home/yaohao/test/asdasdasd",W_OK));

#if 0
  char* ptr=new char[5];
  uint32_t fourcc=0;
  uint32_t fourcc2=0;

  memset(ptr,0,5);
  FILE* wavFile=fopen("x.wav","rb");

  fread(ptr,4,1,wavFile);
  printf("ptr is %s\r\n",ptr);

  fseek(wavFile,0,SEEK_SET);
  fread(ptr,1,4,wavFile);
  printf("ptr is %s\r\n",ptr);

  fseek(wavFile,0,SEEK_SET);
  fread(&fourcc,1,4,wavFile);
  printf("fourcc is %x\r\n",fourcc);


  fseek(wavFile,0,SEEK_SET);
  fread(&fourcc2,1,4,wavFile);
  printf("fourcc2 is %x\r\n",fourcc2);

  printf("FOURCC abcd  is %x\r\n",FOURCC('a','b','c','d'));




  int a1=1;
  int a2=2;
  int a3=3;
  int a4=4;
  int a5=5;
  int a6=6;
  int a7=7;
  int a8=8;
  char s[8]={1,2,3,4,5,6,7,8};
  int l=s[1]<<8 | 0x00ff&(int)(s[0]);
  int l2=s[1]<<8 | s[0];
  float f=(s[1]<<8 | 0x00ff&(int)(s[0]))/(float)(1<<15);
  float f2=(s[1]<<8 | s[0])/(float)(1<<15);
  printf("l is %d\r\n",l);
  printf("l2 is %d\r\n",l2);
  printf("f is %e\r\n",f);
  printf("f2 is %e\r\n",f2);

#endif

  //A a;
  //a.printMyself();

  //test_while();

  //test_fwrite();
  //test_plusplusPoint();
  //test_random(0,101);

  //test_printf();
  //test_switch();

  //malloc_test2();
  //LINK(xiao);
  //printf("%d%d\r\n",xiaovar,varxiao);

  //char *ret =NULL;
  //testNull(ret);
  //S k;
  //printf("distance is %d\r\n",(char*)&(k.b)-(char*)(&k));

  //file_IO();
  //file_fget_test();
  //mkdirRescure();

  //findAllFile("/home/yaohao/yabao/yabao4uof2.0/uof2.0Src/C++/test/UOFTestData");
  //current_dir();

  //print_sizes();
  //test_endian();

  //clock_test();


  int r=0;

  return r;
}

bool mkdirRescure()
{
  //最后不能有‘/’，确保输入是没有的
  const char *d ="dir1";
  int count=0;

  for(size_t i=0;i<strlen(d);i++)
  {
    if(d[i]=='/')
      count++;
  }

  char ** substr=new char*[count];

  int subIndex=0;
  for(size_t i=0;i<strlen(d);i++)
  {
    if(d[i]=='/')
    {
      substr[subIndex]=new char[i+1];
      strncpy(substr[subIndex],d,i);
      substr[subIndex][i]='\0';
      subIndex++;
    }
  }

  for(int i=0;i<count;i++)
  {
    printf("substr %d is %s \r\n",i,substr[i]);
    if( mkdir(substr[i],S_IRWXU))
    {
      if (errno!=EEXIST)
        return false;
    }
  }
  if( mkdir(d,S_IRWXU))
  {
    if (errno!=EEXIST)
      return false;
  }

  for(int i=0;i<count;i++)
    delete [] substr[i];
  delete [] substr;

  return true;
}


void print_sizes()
{
  printf("sizeof int is %d \r\n",sizeof(int));
  printf("sizeof short is %d \r\n",sizeof(short));
  printf("sizeof char is %d \r\n",sizeof(char));
}

void test_endian()
{
  double data;
  RunTime t(__FUNCTION__,data);
  union U
  {
    short a;
    char b;
  };

  U u;
  u.a=0x1234;
  if(u.b==0x34)
    printf("little endian\r\n");
  else if(u.b==0x12)
    printf("big endian\r\n");
  else
    printf("program wrong! \r\n");

}

void current_dir()
{
  char *current_dir=(char*)malloc(200);
  char *ret=getcwd(current_dir,200); 
  if(ret)
  {
    printf("current dir is %s \r\n",current_dir);
  }
  else
    printf("errno is %s\r\n",strerror(errno));
  free(current_dir);

}

#if 0
//for windows
void findAllFileW(char * pFilePath)
{

  WIN32_FIND_DATA FindFileData;
  HANDLE hFind = INVALID_HANDLE_VALUE;
  char DirSpec[MAX_PATH + 1];  // directory specification
  DWORD dwError;

  strncpy (DirSpec, pFilePath, strlen(pFilePath) + 1);
  SetCurrentDirectory(pFilePath);
  strncat (DirSpec, "\\*", 3);

  hFind = FindFirstFile(DirSpec, &FindFileData);

  if (hFind == INVALID_HANDLE_VALUE) 
  {
    printf ("Invalid file handle. Error is %u\n", GetLastError());
    return ;
  } 
  else 
  {
    if (FindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY )
    {
      printf ("    %s\n", FindFileData.cFileName);
    }
    else if(FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY 
            && strcmp(FindFileData.cFileName, ".") != 0
            && strcmp(FindFileData.cFileName, "..") != 0)
    {
      char Dir[MAX_PATH + 1];
      strcpy(Dir, pFilePath);
      strncat(Dir, "\\", 2);
      strcat(Dir, FindFileData.cFileName);

      findAllFile(Dir);
    }

    while (FindNextFile(hFind, &FindFileData) != 0) 
    {
      if (FindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
      {
        printf ("    %s\n", FindFileData.cFileName);
      }
      else if(FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY
              && strcmp(FindFileData.cFileName, ".") != 0
              && strcmp(FindFileData.cFileName, "..") != 0)
      {
        char Dir[MAX_PATH + 1];
        strcpy(Dir, pFilePath);
        strncat(Dir, "\\", 2);
        strcat(Dir, FindFileData.cFileName);
        findAllFile(Dir);
      }

    }

    dwError = GetLastError();
    FindClose(hFind);
    if (dwError != ERROR_NO_MORE_FILES) 
    {
      printf ("FindNextFile error. Error is %u\n", dwError);
      return;
    }
  }
}
#endif 



void findAllFile(char * pFilePath)
{
  DIR * dir;
  dirent * ptr;
  struct stat stStatBuf;
  chdir(pFilePath);
  dir = opendir(pFilePath);

  while ((ptr = readdir(dir)) != NULL)
  {
    if (stat(ptr->d_name, &stStatBuf) == -1)
    {
      printf("Get the stat error on file:%s\n", ptr->d_name);
      continue;
    }
    if ((stStatBuf.st_mode & S_IFDIR) && strcmp(ptr->d_name, ".") != 0
        && strcmp(ptr->d_name, "..") != 0)
    {
      char Path[MAX_PATH];
      strcpy(Path, pFilePath);
      strncat(Path, "/", 1);
      strcat(Path, ptr->d_name);
      findAllFile(Path);
    } 
    if (stStatBuf.st_mode & S_IFREG) 
    {
      printf("  %s\n", ptr->d_name);
    }
    //this must change the directory , for maybe changed in the recured
    chdir(pFilePath);
  } 
  closedir(dir);
}


void get_user_dir()
{
  printf("path = %s\n",getenv("HOME"));
}

bool file_fget_test()
{
  FILE* pf=fopen("/home/yaohao/test/p.py","r");
  int c=0;
  while(true)
  {
    c=getc(pf);
    if(c==EOF)
    {
      printf("it is EOF\r\n");
    }
    printf("c is %x\r\n",c);
  }
  return true;
}


bool file_IO()
{

  FILE* wf=fopen("/home/yaohao/test/wfile","w+");
  FILE* rf=fopen("/home/yaohao/test/rfile","r+");
  FILE* af=fopen("/home/yaohao/test/afile","a+");

  char* buf=new char[1025];
  buf[1024]='\0';

  size_t read_size=0;
  size_t write_size=0;

  while( (read_size=fread(buf,2,1024/2,rf)) >0)
  {
    printf("buf is %s\r\n",buf);
    write_size=fwrite(buf,1,read_size*2,wf);
    printf("read size is %d write size is %d\r\n",read_size,write_size);
  }

  char c='\0';
  while((read_size=fread(&c,1,1,af)) >0 )
  {
    printf("char is %c ftell is %ld\r\n",c,ftell(af));
    write_size=fwrite("a",1,1,af);
    printf("read size is %d write size is %d ftell is %ld\r\n",read_size,write_size,ftell(af));
  }


  fclose(wf);
  fclose(rf);
  fclose(af);
  delete [] buf;

  return true;
}



bool clock_test()
{

  clock_t clock1=clock();
  for(int i=0;i<20000;i++)
    for(int i=0;i<20000;i++)
    {}
  clock_t clock2=clock();
  printf("it has run %f\r\n",(double)clock2-clock1);
  return true;
}


bool get_file_size(const char* fileName)
{
  struct stat stStatBuf;
  if (stat(fileName, &stStatBuf) == -1)
  {
    printf("Get the stat error on file:%s\n", fileName);
    return false;
  }
  printf("%s's size is %ld\r\n",fileName,stStatBuf.st_size);
  if(stStatBuf.st_mode & S_IFREG)
    printf("reg\r\n");
  if(stStatBuf.st_mode & S_IFDIR)
    printf("dir\r\n");

  return true; 
}


bool malloc_test()
{
  int n=0;
  char *m=0;
  while(true)
  {
    cout<<"please input the size(MB) you want to malloc"<<endl;
    cin>>n;
    if(n<0)
      return true;
    else
    {
      try
      {
        m=(char*)malloc(sizeof(char)*n*1024*1024);
        if(!m) 
          throw "malloc failed!"; 
        free(m);
      }
      catch(const char* s)
      {
        cout<<s<<endl;
        return false;
      }
    }
  }
}

bool malloc_test2()
{
  int n=0;
  char *m=0;
  while(true)
  {
    cout<<"please input the size(MB) you want to malloc"<<endl;
    cin>>n;
    if(n<=0)
      return true;
    else
    {
      m=(char*)malloc(sizeof(char)*n*1024*1024);
      if(!m)
        return false;
      free(m);
    }
  }
}

bool test_switch()
{
  int i=0;
  int n=0;
  switch(i)
  {
    i++;
    i=2;
    n=99;

    case 0:
    cout<<"0"<<endl;
    break;

    case 1:
    cout<<"1"<<endl;
    break;

    case 2:
    cout<<"2"<<endl;
    break;

    default:
    cout<<"default"<<endl;   
  }
  cout<<"i is"<<i<<"   n is "<<n<<endl;
  i++;
  cout<<"i is"<<i<<"   n is "<<n<<endl;
  return 0;

}



bool test_printf()
{
  //following show how segment float may happened even use printf
  //  long long i64little=10ll;
  //  long long i64big=99999999999ll;
  //
  //
  //  printf("%s , %d\r\n","luowenlong",i64little);
  //  printf("%s , %d\r\n","luowenlong",i64big);
  //  //up is ok but may wrong i64big value 
  //
  //  printf("%d , %s\r\n",i64little,"luowenlong");
  //  //10 ,(null)
  //  printf("%d , %s\r\n",i64big,"luowenlong");
  //  //segmentation fault

  return 0;
}



bool test_plusplusPoint()
{
  int a[5]={100,200,300,400,500};
  int *p=a;
  printf("%d\r\n",*p++);
  printf("%d\r\n",(*p)++);
  printf("%d\r\n",*(p++));
  for(int i=0;i<5;i++)
  {
    printf("%d\r\n",a[i]);
  }
  return 0;
  //总结++一定是当前所在块的所有操作完了才会执行

}

bool test_fwrite()
{

  FILE* pf=fopen("wfile","wb");
  char *buf=new char[1024];
  memset(buf,'a',1024);
  for(int i=0;i<100;i++)
    for(int i=0;i<1000;i++)
    {
      fwrite(buf,1,1024,pf);
    }
  return true;
}

bool test_random(int startIndex,int endIndex)
{
  if(endIndex<=startIndex)
    return false;
  srand(time((time_t*)0));
  int range=endIndex-startIndex;
  for(int i=0;i<100;i++)
  {
    printf("random is %d\r\n",rand()%range+startIndex);
  }
  return true;
}

bool test_while()
{
  while(true)
  {
    A a;
  }
  return true;
}
void IOTest()
{
  char* buffer = new char[1<<20];
  FILE* pf = fopen("file","wb");
  while(true)
  {
    fwrite(buffer,1,1<<20,pf);
    fseek(pf,0,SEEK_SET);
  }
}
void CPUTest()
{
  for(char i=0; i<1000; i++);
}

void signed_and_unsigned()
{

  printf("long long size is %d\r\n",sizeof(long long));
  long long a=(1ll<<62)-1+(1ll<<62);
  unsigned long long b=(1llu<<63);
  printf("a is %lld\r\n",a);
  printf("b is %llu\r\n",b);

  unsigned long long c = a;

  printf("c is %llu\r\n",c);

}

void argTest(int64_t data)
{
  printf("data is %llu\r\n",data);
  printf("here data is %lld\r\n",data);
}

long UOFCreateDirectory(const char *dirUrl)
{
  size_t dirUrlLength = strlen(dirUrl);
  char* fixedDirUrl=new char[dirUrlLength+1];
  strcpy(fixedDirUrl,dirUrl);
  if(dirUrl[dirUrlLength-1]== SLASH)
  {
    fixedDirUrl[dirUrlLength-1]='\0';
  }

  char *dirDirUrl=getDirDir(fixedDirUrl);
  if(dirDirUrl == NULL)
  {
    delete [] fixedDirUrl;
    return 0;
  }

  if( UOFCreateDirectory(dirDirUrl)!=0)
  {
    delete [] fixedDirUrl;
    delete [] dirDirUrl;
    return -1;
  }

  if(access(fixedDirUrl, F_OK)==0)
  {
    delete [] fixedDirUrl;
    delete [] dirDirUrl;
    return 0;
  }

#ifdef WIN32
  //成功，返回0;最后一个字符不能带/,否则不成功
  if(::CreateDirectoryA((LPCSTR)fixedDirUrl, NULL)!=1)
  {
    delete [] fixedDirUrl;
    delete [] dirDirUrl;
    return -1;
  }
  else
  {
    delete [] fixedDirUrl;
    delete [] dirDirUrl;
    return 0;
  }
#else

  if(mkdir(fixedDirUrl , S_IRWXU)!=0)
  {
    delete [] fixedDirUrl;
    delete [] dirDirUrl;
    return -1;
  }
  else
  {
    delete [] fixedDirUrl;
    delete [] dirDirUrl;
    return 0;
  }


#endif

}

char* getDirDir(const char* dirUrl)
{
  size_t dirDirLength=strrchr(dirUrl,SLASH) - dirUrl;
  if(dirDirLength<=0)
  {
    return NULL;
  }

  char * dirDirUrl=new char[dirDirLength+1];
  strncpy(dirDirUrl,dirUrl,dirDirLength);
  dirDirUrl[dirDirLength]='\0';

  return dirDirUrl;
}

int test_getpwnam()
{
  struct passwd * pw;
  char *username = "yaohao";
  pw = getpwnam(username);
  if (!pw) {
    printf("%s is not exist\n", username);
    return -1;
  }
  printf("pw->pw_name = %s\n", pw->pw_name);
  printf("pw->pw_passwd = %s\n", pw->pw_passwd);
  printf("pw->pw_uid = %d\n", pw->pw_uid);
  printf("pw->pw_gid = %d\n", pw->pw_gid);
  printf("pw->pw_gecos = %s\n", pw->pw_gecos);
  printf("pw->pw_dir = %s\n", pw->pw_dir);
  printf("pw->pw_shell = %s\n", pw->pw_shell);
  return 0;
}


void test_mem()
{
  const char *p = "abcd";

  memcpy((char*)p,"efgh",4);
}

