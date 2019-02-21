function CLog(logstr)
{
    CLogToFile("CLog", logstr)
    log(logstr)
}
function CLogToFile(logtag, logstr)
{
    var nsStrLog = NSString.alloc().initWithString(logstr);
    nsStrLog = nsStrLog.stringByAppendingFormat("\n");

    var homeDir = NSHomeDirectory();
    var logFileFullName = homeDir + "/" + logtag + ".txt"

    var filehandle = NSFileHandle.fileHandleForWritingAtPath(logFileFullName)
    if(filehandle)
    {
        filehandle.truncateFileAtOffset(filehandle.seekToEndOfFile());
        var nsdata = nsStrLog.dataUsingEncoding(NSUTF8StringEncoding);
        filehandle.writeData(nsdata)
        [filehandle closeFile];
    }
    else
    {
        nsStrLog.writeToFile_atomically(logFileFullName, true);
    }
}

function getSelections(context)
{
    return context.selection
}
function getFirstSelection(context)
{
    var selection = nil;
    var selections = getSelections(context);
    if(selections && selections.length > 0)
    {
        selection = selections[0];
    }
    return selection;
}
function getCurrentPage(context)
{
    var doc = context.document;
    return doc.currentPage();
}
function getFirstPage(context)
{
    var doc = context.document;
    var pages = doc.pages();
    for(var iPage=0; iPage<pages.length; iPage++)
    {
        return pages[iPage];
    }
    return nil; 
}
function getLastPage(context)
{
    var doc = context.document;
    var pages = doc.pages();
    for(var iPage=0; iPage<pages.length; iPage++)
    {
        return pages[pages.length-1];
    }
    return nil; 
}

function getFirstArtboardInPage(pageObj)
{
    var artboards = pageObj.artboards();
    for(var iArtboard=0; iArtboard <artboards.length; iArtboard ++)
    {
        return artboards[iArtboard];
    }
    return nil; 
}
function getFirstArtboard(context)
{
    var firstPage = getFirstPage(context);
    return getFirstArtboardInPage(firstPage); 
}

function getFirstLayerInArtboard(artboardObj)
{
    var layers = artboardObj.layers();
    for(var iLayer=0; iLayer <layers.length; iLayer ++)
    {
        return layers[iLayer];
    }
    return nil; 
}

function getFirstLayer(context)
{
    var firstArtboard = getFirstArtboard(context)
    return getFirstLayerInArtboard(firstArtboard); 

    // var doc = context.document;
    // var pages = doc.pages();
    // var page = pages[0];
    // var artboards = page.artboards();
    // var artboard = artboards[0];
    // var layers = artboard.layers()
    // var layer = layers[0];
}

function getAllLayers(layer, layersList)
{
    layersList.push(layer);
    if(layer.containsLayers())
    {
        var subLayers = layer.layers()
        for(var idxSub=0; idxSub < subLayers.count(); idxSub++)
        {
            var sublayer = subLayers[idxSub];
            getAllLayers(sublayer, layersList)
        }
    }
}

function getObjectByID(context, objectID)
{
    return context.document.documentData().layerWithID(objectID)
}

function getPageArtboard(pageObj, artboardID)
{
    return pageObj.artboardWithID(artboardID);
}

function indexOfLayerInParent(context, layer)
{
    if(layer.className() == "MSPage")
    {
        var pages = context.document.pages();
        for(var iPage=0; iPage <pages.length; iPage ++)
        {
            if(pages[iPage].objectID() == layer.objectID())
            {
                return iPage;
            }
        }
    }
    else
    {
        var parent = layer.parentGroup();
        return parent.indexOfLayer(layer);
    }
    return -1;
}


function getLayerLocationByID(context, objectID)
{
    var locationStr = nil;
    var layer = context.document.documentData().layerWithID(objectID);
    while(true)
    {
        if (nil == layer) {
            break;
        };

        var index = indexOfLayerInParent(context, layer);
        var curStepName = "[" + index + "]" + layer.name()
        if (locationStr) {
            locationStr = curStepName + " -> " + locationStr;
        }
        else
        {
            locationStr = curStepName
        }
        layer = layer.parentGroup();
    }
    
    return locationStr;
}

function printLayersSpecial(context, layer, func = nil)
{
    var layerList = []
    getAllLayers(layer, layerList);
    for (var i = 0; i < layerList.length; i++) {
        var checkLayer = layerList[i]
        var bResult = func(checkLayer)
        if (bResult) {
            var location = getLayerLocationByID(context, checkLayer.objectID());
            log(location);
        };
    };
}

function CocoaDictArrToJsonObj(xObj)
{
    var jsonObj = "UnknownObject";
    if(xObj.className().indexOf("String")>0)
    {
        jsonObj = xObj.toString()+"";
    }
    else if(xObj.className().indexOf("Number")>0)
    {
        jsonObj = Number(xObj);
    }
    else if(xObj.className().indexOf("Dictionary")>0)
    {
        jsonObj = {}
        for(key in xObj)
        {
            var localkey = key
            var xSubObj = xObj[key];
            var jsonSub = CocoaDictArrToJsonObj(xSubObj)
            jsonObj[localkey]= jsonSub
        }
    }
    else if(xObj.className().indexOf("Array")>0)
    {
        jsonObj = []
        for(iArr=0;iArr<xObj.count();iArr++)
        {
            var xSubObj = xObj[iArr]
            var jsonSub = CocoaDictArrToJsonObj(xSubObj)
            jsonObj.push(jsonSub)
        }
    }
    return jsonObj
}

function JsonObjToCocoaDictArr(jObj)
{
    var xObj = @"UnknownObject";
    if(typeof(jObj) == "string") // ""
    {
        xObj = [NSString stringWithString:jObj];
    }
    else if(typeof(jObj) == "number") // number
    {
        xObj = jObj;
    }
    else if((jObj instanceof Object) && !(jObj instanceof Array)) // {}
    {
        xObj = [NSMutableDictionary dictionary];
        for(key in jObj)
        {
            var localkey = key
            var jSubObj = jObj[key];
            var xSub = JsonObjToCocoaDictArr(jSubObj)
            [xObj setObject:xSub forKey:localkey];
        }
    }
    else if((jObj instanceof Object) && (jObj instanceof Array)) // []
    {
        xObj = [NSMutableArray array];
        for(iArr=0;iArr<jObj.length;iArr++)
        {
            var jSubObj = jObj[iArr]
            var xSub = JsonObjToCocoaDictArr(jSubObj)
            xObj.addObject(xSub);
        }
    }
    return xObj;
}

function readFileContent(filename)
{
    var fileManger = [NSFileManager defaultManager];
    if(![fileManger fileExistsAtPath:filename]){
        return nil;
    }
    var infh = [NSFileHandle fileHandleForReadingAtPath:filename];
    if(!infh){
        return nil;
    }
    var nsDataContent =  [infh readDataToEndOfFile];
    [infh closeFile];
    var strContents = [[NSString alloc] initWithData:nsDataContent encoding:NSUTF8StringEncoding];
    return strContents;
}

function getJsonObjectFromJsonString(jsonString)
{
    return JSON.parse(jsonString);
}

function getJsonStringFromJsonObject(JsonObject)
{
    return JSON.stringify(JsonObject);
}

function JsonPrettyString(jsonObject)
{
    var err = 0;
    var nsJsonData = [NSJSONSerialization dataWithJSONObject:jsonObject options:NSJSONWritingPrettyPrinted error:err];
    var jsonString = [[NSString alloc] initWithData:nsJsonData encoding:NSUTF8StringEncoding];
    return jsonString;
}


