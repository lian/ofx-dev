//
//  WidgetsEnableTransformer2.m
//  DarwiinRemote
//
//  Created by KIMURA Hiroaki on 06/12/20.
//  Copyright 2006 KIMURA Hiroaki. All rights reserved.
//

#import "WidgetsEnableTransformer2.h"


@implementation WidgetsEnableTransformer2
+ (Class)transformedValueClass{
	return [NSNumber self];
}

+ (BOOL)allowsReverseTrasformation{
	return NO;
}


- (id)transformedValue:(id)beforeObject{
	
	
	if (beforeObject == nil) return nil;
	
	
	switch([beforeObject intValue]){
		
		case 1:
			return [[NSNumber alloc] initWithBool:YES];
		default:
			return [[NSNumber alloc] initWithBool:NO];
			
	}
}
@end
