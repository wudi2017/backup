//
//  SExportListSelectView.m
//  sketchPluginFramework
//
//  Created by navibase on 2018/7/4.
//  Copyright © 2018年 iauto. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "SExportListSelectView.h"
#include "SCheckBox.h"

@implementation SExportListSelectView

-(instancetype)init {
    self = [super init];
    
    int iViewH = 360;
    int iViewW = 360;
    
    [super setFrame:NSMakeRect(0,0,iViewW,iViewH)];
    [super setWantsLayer:YES];
    CALayer * layer = [super layer];
    NSColor * tstNSColor = [NSColor colorWithRed:1 green:0 blue:0 alpha:0.3];
    [layer setBackgroundColor:[tstNSColor CGColor]];
    
    NSScrollView * scroll = [[NSScrollView alloc] init];
    [scroll setFrame:NSMakeRect(15, 140, 330, 200)];
    NSView *  scrContent = [[NSView alloc] init];
    [scrContent setFrame:NSMakeRect(0, 0, 330, 600)];
    [scrContent setWantsLayer:true];
    [[scrContent layer] setBackgroundColor:CGColorCreateGenericRGB(0.0, 0.8, 0.0, 0.2)];
    {
        for(int i=0; i<20; i++)
        {
            SCheckBox * cb = [[SCheckBox alloc] init];
            [cb setFrame:NSMakeRect(20, i*25, 100, 25)];
            [cb setText:@"Select All"];
            [scrContent addSubview:cb];
        }
    }
    
    [scroll setDocumentView:scrContent];
    [scroll setHasVerticalScroller:true];
    
    NSPoint pt = NSMakePoint(0.0, [[scroll documentView] bounds].size.height);
    [[scroll documentView] scrollPoint:pt];
    
    [super addSubview:scroll];
    
    
    
    SCheckBox * cb1 = [[SCheckBox alloc] init];
    [cb1 setFrame:NSMakeRect(70, 100, 100, 25)];
    [cb1 setText:@"Select All"];
    [super addSubview:cb1];
    
    SCheckBox * cb2 = [[SCheckBox alloc] init];
    [cb2 setFrame:NSMakeRect(200, 100, 100, 25)];
    [cb2 setText:@"Inverse"];
    [super addSubview:cb2];
    
    NSButton * btn1 = [[NSButton alloc] init];
    [btn1 setFrame:NSMakeRect(55, 55, 250, 35)];
    [btn1 setTitle:@"Export to the same file"];
    [super addSubview:btn1];
    
    NSButton * btn2 = [[NSButton alloc] init];
    [btn2 setFrame:NSMakeRect(55, 15, 250, 35)];
    [btn2 setTitle:@"Export to the different file"];
    [super addSubview:btn2];
    
//    var scrollView = NSScrollView.alloc().init();
//    scrollView.frame = NSMakeRect(0, 0, 200, 200);
//    var scrollViewContent = NSView.alloc().init();
//    scrollViewContent.frame = NSMakeRect(0, 0, 300, 300);
//    scrollViewContent.setWantsLayer(true);
//    var scrollViewContentLayer = CALayer.layer();
//    scrollViewContentLayer.setBackgroundColor(CGColorCreateGenericRGB(0.0, 0.8, 0.0, 0.2));
//    scrollViewContent.setLayer(scrollViewContentLayer);
//    var testButton = NSButton.alloc().initWithFrame(NSMakeRect(20, 20, 40, 40));
//    testButton.setAttributedTitle("test");
//    testButton.setBordered(true);
//    testButton.setCOSJSTargetFunction(function(sender){
//        context.document.showMessage('test')
//    });
    
//    scrollViewContent.addSubview(testButton);
//    scrollView.documentView = scrollViewContent
//    scrollView.hasVerticalScroller = true
//    scrollView.setDrawsBackground(false)
    
    
    return self;
}

@end
