//
//  SWaitPanel.m
//  sketchPluginFramework
//
//  Created by navibase on 2018/7/7.
//  Copyright © 2018年 iauto. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "SWaitPanel.h"

@implementation SWaitPanel

-(instancetype)init
{
    self = [super init];
    
    self.m_panel = [[NSPanel alloc] init];
    
    [self.m_panel setFrame:NSMakeRect(0, 0, 1600, 800) display:false];
    [self.m_panel center];
    [self.m_panel setAlphaValue:1];
    
    [self.m_panel setStyleMask:NSNonactivatingPanelMask];
    [self.m_panel becomeKeyWindow];
    [self.m_panel becomeMainWindow];
    [self.m_panel setMovableByWindowBackground:true];
    [self.m_panel setFloatingPanel:true];
    [self.m_panel setLevel:NSStatusWindowLevel];
    
    
    return self;
}

-(void)show
{
    [self.m_panel makeKeyAndOrderFront:nil];
    [self.m_panel setFrame:NSMakeRect(0, 0, 1600, 800) display:false];
    
    [NSApp runModalForWindow:self.m_panel];
}

-(void)hide
{
    [self.m_panel setFrame:NSMakeRect(0, 0, 0, 0) display:false];
}

@end
