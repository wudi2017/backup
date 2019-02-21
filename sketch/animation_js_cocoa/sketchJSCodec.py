# coding=utf-8
import time
import datetime
import sys
import os
import shutil
import random

### --- global vars ------------------------------------------------------------
allFileCount = 0
handFileCount = 0
findFuncList = []

### --- DebugLog ---------------------------------------------------------------
PyDbgLogStatus = False
EnableTimeStrFlg = False
logfilename = None
logcallback = None
EnableLogColer = True
def highlight(s):  
    global EnableLogColer
    if EnableLogColer:
        return "%s[30;2m%s%s[1m"%(chr(27), s, chr(27))  
    else:
        return s
def inRed(s):  
    global EnableLogColer
    if EnableLogColer:
        return highlight('') + "%s[1;31;1m%s%s[0m"%(chr(27), s, chr(27)) 
    else:
        return s
def inGreen(s):  
    global EnableLogColer
    if EnableLogColer:
        return highlight('') + "%s[1;32;1m%s%s[0m"%(chr(27), s, chr(27)) 
    else:
        return s
def inGray(s):  
    global EnableLogColer
    if EnableLogColer:
        return  highlight('') + "%s[37;2m%s%s[0m"%(chr(27), s, chr(27)) 
    else:
        return s
def SetLogCallback(log_cb):
    global logcallback
    logcallback = log_cb
    return
def EnableLogColer(enableFlag):
    global EnableLogColer
    EnableLogColer = enableFlag
    return
def PyLog(logstr):
    global logfilename
    logheader = ""
    if EnableTimeStrFlg:
        cur=datetime.datetime.now()
        hourstr = str(cur.hour)
        if len(hourstr)==1:
            hourstr = "0" + hourstr
        minutestr = str(cur.minute)
        if len(minutestr)==1:
            minutestr = "0" + minutestr
        secondstr = str(cur.second)
        if len(secondstr)==1:
            secondstr = "0" + secondstr
        LogTime = hourstr + ":" + minutestr + ":" + secondstr
        logheader = ""+LogTime+": "
    else:
        logheader = ""
    strbuf = logheader+logstr
    if logfilename is not None:
        writebuf = ""
        buflist = strbuf.split(chr(27))
        if len(buflist) == 5:
            buflist[3] = buflist[3].replace("[1;31;1m","")
            buflist[3] = buflist[3].replace("[1;32;1m","")
            buflist[3] = buflist[3].replace("[37;2m","")
            buflist[4] = buflist[4].replace("[0m","")
            writebuf = buflist[0] + buflist[3] + buflist[4]
        else:
            writebuf = strbuf
        fileobj = open(logfilename,"a")
        fileobj.write(writebuf + "\n")
        fileobj.close()
    print(strbuf)
    if logcallback != None:
        logcallback(strbuf)
    return
def SetPyLogFileName(filename):
    global logfilename
    logfilename = filename
    return
def SetPyDbgLogStatus(EnableDbgLog=False,EnableTimeStr=False):
    global PyDbgLogStatus
    global EnableTimeStrFlg
    PyDbgLogStatus = EnableDbgLog
    EnableTimeStrFlg = EnableTimeStr
    return
def GetPyDbgLogStatus():
    global PyDbgLogStatus
    return PyDbgLogStatus
def PyDbgLog(logstr):
    global PyDbgLogStatus
    if PyDbgLogStatus:
    #if True:
        PyLog(logstr)
    return


###################################################################################

def outResult(lineStr):
	obj = open('result.log','a+')
	obj.write(lineStr+"\r\n")
	obj.close()
	return

def GetCharCount(content, k):
	count = 0
	for i in range(len(content)):
		c = content[i]
		if k == c:
			count = count+1
	return count

def GetEncode(filename):
    return "unknown"
    import chardet
    file_object = open(filename,'rb')
    file_content_bytes = file_object.read()
    file_object.close()
    adchar=chardet.detect(file_content_bytes)
    encodingStr = adchar['encoding']
    return str(encodingStr)

def isCallFunc(line, findFuncName):
	pos_key = line.find(findFuncName)
	if pos_key >= 0:

		# keyword check: NOT ~ _ 0-9 a-z A-Z
		check1 = False
		pos_pre = pos_key-1
		if pos_pre >= 0:
			preChar = line[pos_pre]
			ascCode = ord(preChar)
			if preChar == '_' or \
				preChar == '~'  or\
				(ascCode >= 48 and ascCode <= 57) or \
				(ascCode >= 65 and ascCode <= 90) or (ascCode >= 97 and ascCode <= 122):
				pass
			else:
				check1 = True

		# check ""string
		check2 = False
		if pos_pre >= 0:
			subleftline = line[0:pos_pre]
			#print(subleftline)
			semiconlonCnt = GetCharCount(subleftline,'"')
			#print(semiconlonCnt)
			if semiconlonCnt%2 == 0:
				check2 = True

		# check comments
		check3 = False
		if pos_pre >= 0:
			subleftline = line[0:pos_pre]
			posCommentsStart1 = subleftline.find("//")
			posCommentsStart2 = subleftline.find("/*")
			if posCommentsStart1 >=0 or posCommentsStart2 >= 0:
				check3 = False
			else:
				check3 = True

		if check1 and check2 and check3:
			return True 
	return False

def isHandleFileType(filename):
	if filename.endswith(".js"):
		return True
	return False

confusedCode = [
"{ var ijk1=10; testobj=20; b3=ijk1+testobj;}",
"{  }",
"{var listControl=[3,4,10,3];}",
"{ var i=14; }",
"{ var j=15536; }",
"{ var m=13;}",
"{ var b6b=18; var sum = b6b; var z=10; sum=z+b6b; }",
"{ var b6s=18; var sum = b6s; var z=10; sum=z+b6s; }",
"{ var b66=18; var sum = b66; var z=10; sum=z+b66; }",
"{ var allFileCount=20;var allFileNameCount=21;var allFileNameCount1=22;var allFileNameCount2=23; }",
"{ var allFileCountS=20;var allFileNameCountS=21;var allFileNameCount1S=22;var allFileNameCount2S=23; }",
"{ var z16=14; }",
"{function testbuildXValue(){ var s=20; s=100; s=300;}}",
"{function testbuildYValue(){ var s=20; s=100; s=300;}}",
"{function testbuildXValue(){ var s=20; s=100; s=300;}}",
# "{function buildControlButton(){ var buildx = 30;  var andFileCount = 1; }}",
# "{function buildListButton(){ var buildList = 30;  var buildListX = 125;var buildList1 = 152; }}",
# "{function buildViewListButton(){ var buildx = 30;  var andFileCount = 1; }}",
# "{function funcT1(x1,  x2){console.log('func2 begin'); sum = x1+x2;console.log('    x1+x2=' + sum);}}",
# "{function funcT2(x1,  x2){console.log('func2 begin'); sum = x1+x2;console.log('    x1+x2=' + sum);}}",
# "{function funcT3(x1,  x2){console.log('func2 begin'); sum = x1+x2;console.log('    x1+x2=' + sum);}}",
# "{function funcT4(x1,  x2){console.log('func2 begin'); sum = x1+x2;console.log('    x1+x2=' + sum);}}",
# "{function funcT5(x1,  x2){console.log('func2 begin'); sum = x1+x2;console.log('    x1+x2=' + sum);}}",
# "{function funcT6(x1,  x2){console.log('func2 begin'); sum = x1+x2;console.log('    x1+x2=' + sum);}}",
"/* function testbuildYValue(){ var s=20; s=100; s=300;} */",
"/* if isHandleFileType(filename): */",
"/* handFileCount = handFileCount + 1*/",
"/* sys.stdout.writelines('  */",
"/* unused code*/",
"/* this is testcode*/",
]
def getConfusedCode():
	global confusedCode
	iLen = len(confusedCode)
	iRandom = random.randint(0,iLen-1)
	code = confusedCode[iRandom];
	return code;

def rmCommnetL(content):
    filecontent = content
    rmCommentLContent = ""
    while len(filecontent) > 0:
        commentLPos = filecontent.find("//")
        if commentLPos >=0:
            rmCommentLContent += filecontent[0:commentLPos];
            filecontent = filecontent[commentLPos:]
            commentLPosE = filecontent.find("\n")
            if commentLPosE >= 0:
                filecontent = filecontent[commentLPosE:]
            else:
                filecontent = "";
        else:
            rmCommentLContent += filecontent;
            filecontent = "";
    return rmCommentLContent
def rmCommnetS(content):
    filecontent = content
    rmCommentSContent = ""
    while len(filecontent) > 0:
        commentSPos = filecontent.find("/*")
        if commentSPos >=0:
            rmCommentSContent += filecontent[0:commentSPos];
            filecontent = filecontent[commentSPos:]
            commentSPosE = filecontent.find("*/")
            if commentSPosE >= 0:
                filecontent = filecontent[commentSPosE+2:]
            else:
                filecontent = "";
        else:
            rmCommentSContent += filecontent;
            filecontent = "";
    return rmCommentSContent
def addUnusedConfusedCode(content):
    filecontent = content
    newContent = ""
    while len(filecontent) > 0:
        curLine = ""
        newLinePos = filecontent.find("\n")
        if newLinePos >= 0:
            curLine = filecontent[0:newLinePos];
            filecontent = filecontent[newLinePos+1:]
        else:
            curLine = filecontent
            filecontent = ""
        curLine = curLine + "\n"

        # deal with line begin
        if curLine.strip("\n").rstrip(" ").endswith(";"):
            curLine = curLine.strip("\n")
            confcode = getConfusedCode();
            curLine+=confcode
        if curLine.strip("\n").endswith("{") or curLine.strip("\n").endswith("}"):
            curLine = curLine.strip("\n")
        if curLine.strip("\n").startswith("{"):
            newContent = newContent.rstrip("\n") 
        if curLine.strip("\n").strip(" ") == "":
            continue
        # deal with line end

        newContent += curLine
    return newContent

def DParse(content):
    parsedContent = ""

    curStatus = "unknowncode" ; # unknowncode comments string
    specCharStack = []
    curString = ""

    specCharStack.append('a')
    specCharStack.append('b')
    specCharStack.append('c')
    print(specCharStack.pop())
    print(specCharStack.pop())
    print(specCharStack.pop())

    for cIndex in xrange(0,len(content)):
        c = content[cIndex];

        stacktop = ""
        if len(specCharStack) > 0:
            stacktop = specCharStack[len(specCharStack)-1]

        if c == stacktop:
            if stacktop == '\'':
                pass

        if c == "\"":
            curStatus == "string"

        parsedContent += c;
    return parsedContent

def DealFile(filename):
    global allFileCount
    global handFileCount
    # filename filter
    if isHandleFileType(filename):
        handFileCount = handFileCount + 1
        encodingStr = GetEncode(filename)
        PyDbgLog("File: " + filename + " encoding:" + encodingStr)
        sys.stdout.writelines('                                                                                                                                               \r')
        sys.stdout.writelines("(" + str(handFileCount) + "/" + str(allFileCount) + ") " + filename + "\n")
        sys.stdout.flush()

        if encodingStr=="ascii" or encodingStr=="utf-8" or  encodingStr=="gbk" or  encodingStr=="SHIFT_JIS":
            #PyDbgLog("    File: " + filename + " encoding:" + encodingStr)
            pass
        else:
            #PyDbgLog("    File: " + filename + " encoding:" + encodingStr)
            pass

        file_object = open(filename,'rb')
        filecontent = file_object.read();
        file_object.close()
        #print(filecontent)

        ccc = DParse(filecontent);
        print(ccc)

        #filecontent = rmCommnetL(filecontent);

        #filecontent = rmCommnetS(filecontent);

        #filecontent = addUnusedConfusedCode(filecontent);

        #print(filecontent)

        # rm origin file
        if os.path.exists(filename):
            #os.remove(filename)
            pass
            
        # write new file
        filenameTmp = filename+"_tmp.js"
        #filenameTmp = filename
        if os.path.exists(filenameTmp):
            os.remove(filenameTmp)
        file_object_new = open(filenameTmp,'a+')
        file_object_new.write(filecontent)
        file_object_new.close()

    else:
        #PyDbgLog("    File: " + filename + " IGNORE")
        pass
    return


def Main():
    SetPyDbgLogStatus(False)
    PyDbgLog("### Main Begin")
    SourceDirList = [
        #"/home/u/backup/custom-search.py",
        "/Users/navibase/sketch-iauto/JSTool/sketchjs/test.js",
        #"/Users/navibase/sketch19/sketchplugin/iautoPlugin.sketchplugin/Contents/Sketch/commonlib",
        #"/Users/navibase/sketch19/sketchplugin/iautoPlugin.sketchplugin/Contents/Sketch/libGenerator",
        #"/Users/navibase/sketch19/sketchplugin/iautoPlugin.sketchplugin/Contents/Sketch/libJSonDB",
        ]

    global allFileCount
    for fulldirname in SourceDirList:
        if os.path.islink(fulldirname):
            PyDbgLog("Link: " + fulldirname)
        elif os.path.isfile(fulldirname):
            if isHandleFileType(fulldirname):
                allFileCount = allFileCount + 1
        elif os.path.isdir(fulldirname):
            PyDbgLog("Dir: " + fulldirname)
            for parent,dirnames,filenames in os.walk(fulldirname):
                for filestr in filenames:
                    orifilefullname = parent + os.sep + filestr
                    if isHandleFileType(orifilefullname):
                        allFileCount = allFileCount + 1
        else:
            PyDbgLog("NotFound: " + fulldirname)
    PyLog("allFileCount: " + str(allFileCount))

    for fulldirname in SourceDirList:
        if os.path.islink(fulldirname):
            PyDbgLog("Link: " + fulldirname)
        elif os.path.isfile(fulldirname):
            DealFile(fulldirname)   
        elif os.path.isdir(fulldirname):
            PyDbgLog("Dir: " + fulldirname)
            for parent,dirnames,filenames in os.walk(fulldirname):
                for filestr in filenames:
                    orifilefullname = parent + os.sep + filestr
                    DealFile(orifilefullname)
        else:
            PyDbgLog("NotFound: " + fulldirname)

    PyDbgLog("### Main End")
    return


if __name__ == '__main__':
    #reload(sys)
    #sys.setdefaultencoding('utf-8')
    Main()