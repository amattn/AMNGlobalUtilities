# Real Life Global Utilities

Typically you want to install this in the YOURPROJECT-Prefix.pch file like so:

    #ifdef __OBJC__
    	#import <UIKit/UIKit.h>
    	#import <Foundation/Foundation.h>
    	#import "RLGlobalUtilities.h"
    #endif

