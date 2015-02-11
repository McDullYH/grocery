#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

#include <iostream>
#include <list>
#include <string>


#ifdef WIN32 
#define fseeko _fseeki64
#define __int64 off_t
#else
#include <unistd.h>
#include <dirent.h>
#endif

using namespace std;



/// \brief get all file absolute path of a dir  the dir name not include last '/'
/// \param dir The director you want to get its file names
/// \param fileNames file names container 
/// \param recursive get file names recursive if it is true
/// \prarm filterString file name not include 
/// \return 0 if success 
///

int getAllFilePath(const string dir,list<string> &fileNames,const bool recursive,const string filterString="")
{
  char *cDir=new char[dir.length()+1];
  strcpy(cDir,dir.c_str());

  if(access(cDir,R_OK))
  {
    return -1;
  }

  DIR *pDir=opendir(cDir);
  if(!pDir)
  {
    return -2;
  }

  struct stat statBuf;
  dirent *pDirEnt=0;

  while(pDirEnt = readdir(pDir))
  {
    chdir(cDir);
    if(stat(pDirEnt->d_name,&statBuf)!=-1)
    {
      if(statBuf.st_mode & S_IFDIR && recursive && strcmp(pDirEnt->d_name,"..") && strcmp(pDirEnt->d_name,"."))
      {
        string dirName=dir + "/" + pDirEnt->d_name;
        if(getAllFilePath(dirName,fileNames,recursive,filterString) !=0)
        {
          return -3;
        }
      }
      else if(statBuf.st_mode & S_IFREG)
      {
        string fileName= dir + "/" + pDirEnt->d_name;
        if(filterString.empty() || fileName.find(filterString) == string::npos)
        {
          fileNames.push_back(fileName);
        }
      }
    }
  }
  return 0;
}


//no recursive 
int renameSort(const string dir,int startNum=1)
{
  list<string> fileNames;
  if(getAllFilePath(dir,fileNames,false)!=0)
  {
    return -1;
  }
  unsigned int size=fileNames.size();
  unsigned int numLen=1;
  while((size=size/10) > 0)
  {
    numLen++;
  }
  char *numStr = new char [numLen+1];
  {
    int i= startNum;
    string subStr;
    for(list<string>::const_iterator citer=fileNames.begin(); citer!=fileNames.end(); citer++,i++)
    {
      sprintf(numStr,"%0*d",numLen,i);
      subStr=citer->substr(citer->rfind('.'),citer->length());
      subStr=numStr+subStr;
      if(access(subStr.c_str(),R_OK) == 0 )
      {
        continue;
      }
      if(rename(citer->c_str(),subStr.c_str()))
      {
        cout<<"file name is "<<*citer<<"  error is "<<strerror(errno)<<endl;
        return -2;
      }
    }
  }
  delete []numStr;
  return 0;
}

//acturally it can be done by linux shell and regEx
//it is recursive
int addSuffix(const string dir,const string suffix)
{
  list<string> fileNames;
  if(getAllFilePath(dir,fileNames,true)!=0)
  {
    return -1;
  }
  for(list<string>::const_iterator citer=fileNames.begin(); citer!=fileNames.end(); citer++)
  {
    if(rename(citer->c_str(),(*citer+suffix).c_str()))
    {
      cout<<"file name is "<<*citer<<"  error is "<<strerror(errno)<<endl;
      return -2;
    }
  }
  return 0;
}

//it is recursive,cut from last,once one cut
int cutName(const string dir,const string cutStr)
{
  list<string> fileNames;
  if(getAllFilePath(dir,fileNames,true)!=0)
  {
    return -1;
  }

  string tempStr;
  size_t startPos =0;
  for(list<string>::const_iterator citer=fileNames.begin(); citer!=fileNames.end(); citer++)
  {
    if(citer->substr(citer->rfind('/')+1,citer->length()).length() <= cutStr.length())
    {
      continue;
    }
    startPos=citer->rfind(cutStr);
    if (startPos==string::npos)
    {
      continue;
    }
    tempStr=*citer;
    if(rename(citer->c_str(),tempStr.replace(startPos,cutStr.length(),"").c_str() ) )
    {
      cout<<"file name is "<<*citer<<"   error is "<<strerror(errno)<<endl;
      //if has a same name ,it will failed
      return -2;
    }
  }
  return 0;
}


int cutBlank(const string dir)
{
  return cutName(dir," ");
}


/*
   if it is a dir  ,it will end with '/'
   if it is a file ,it won't end with '/'

   input the inName 
   output the outName
   don't malloc for outName,this function will malloc itself

   can handle  "\\\\"
   not handle "//" bcs it may be protocol! and '//' in path is all ok
*/
int flapFileOrDirName(const char* inName,char* &outName)
{
  outName=new char[strlen(inName+1+1)];
  //one for \0 and one for possiable '/'
  //step 1, change all '\'  and '\\' to '/'

  bool lastCharIsSlash=false;
  int o=0;
  for(int i=0; i<strlen(inName)+1; i++)
  {
    if(inName[i] == '\\')
    {
      if(lastCharIsSlash)
      {
        continue;
      }
      else
      {
        outName[o]='/';
        o++;
      }
      lastCharIsSlash=true;
    }
    else
    {
      outName[o]=inName[i];
      o++;
      lastCharIsSlash=false;
    }
  }
  //now o points to the index of '\0' + 1

  //step 2, checke whether is a file or dir

  printf("before %s\r\n",inName);
  if(access(outName,R_OK) !=0 )
  {
    return -1;
  }

  struct stat statBuf;
  if(stat(outName,&statBuf)!=0)
    return -2;

  if(statBuf.st_mode & S_IFDIR)
  {
    if(outName[o-2]!='/')
    {
      outName[o-1]='/';
      outName[o]='\0';
    }
  }
  else
  {
    return -3;
  }
  printf("after %s\r\n",outName);
  return 0;
}


void test()
{
//    list<string> fileNames;
//    getAllFilePath("/home/yaohao/test_file/UOFTestData",fileNames,false,"");
//    for(list<string>::const_iterator citer=fileNames.begin(); citer!=fileNames.end(); citer++)
//    {
//      cout<<*citer<<endl;
//    }
//    cout<<"fileNames size is "<<fileNames.size()<<endl;
//  
//    fileNames.clear();
//    getAllFilePath("/home/yaohao/test_file/UOFTestData",fileNames,true,"tar");
//    for(list<string>::const_iterator citer=fileNames.begin(); citer!=fileNames.end(); citer++)
//    {
//      cout<<*citer<<endl;
//    }

  //renameSort("/home/yaohao/dir");
  //addSuffix("/home/yaohao/dir",".ra");
  //cutName("/home/yaohao/dir","1");


  //char* s;
  //flapFileOrDirName("/home/yaohao/test",s);
  //flapFileOrDirName("/home//yaohao//test/",s);
  //flapFileOrDirName("/home\yaohao//test",s);
  //flapFileOrDirName("/home\\\yaohao/test",s);



  char buffer[100];
  FILE* pf=fopen("3000M","rb");
  fread(buffer,1,99,pf);
  buffer[100]='\0';
  printf("buffer is %s\r\n",buffer);
  fclose(pf);


  unsigned int offset=(1u<<30)*3-20;
  printf("offset is %u\r\n",offset);

  off_t offset2=(1u<<30)*3-20;
  printf("offset is %lld\r\n",offset2);
  //remember to free s
}


off_t UOFfseek(FILE* stream, off_t offset, int whence)
{
  return fseeko(stream,offset,whence);
}


int main(int argc,char* argv[])
{
  test();
  return 0;
}
