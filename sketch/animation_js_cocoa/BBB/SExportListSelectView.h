//
//  SExportListSelectView.h
//  sketchPluginFramework
//
//  Created by navibase on 2018/7/4.
//  Copyright © 2018年 iauto. All rights reserved.
//

#ifndef SExportListSelectView_h
#define SExportListSelectView_h

#import <Cocoa/Cocoa.h>

@interface SExportListSelectView : NSView

-(instancetype)init;

@property NSMutableArray* m_arrScreenCheckBox;

/*
 model data (NSMutableDictionary NSMutableArray)
 
 modelData =
 {
     "ScreenList":
     {
        "Screen1":"1",
        "Screen2":"0"
        "Screen3":"1"
     }
 }
 
 */

@end

#endif /* SExportListSelectView_h */
