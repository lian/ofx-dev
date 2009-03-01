//
//  WidgetsEnableTransformer.m
//  DarwiinRemote
//
//  Created by KIMURA Hiroaki on 06/12/20.
//  Copyright 2006 KIMURA Hiroaki. All rights reserved.
//

#import "WidgetsEnableTransformer.h"


@implementation WidgetsEnableTransformer

+ (Class)transformedValueClass{
	return [NSNumber self];
}

+ (BOOL)allowsReverseTrasformation{
	return NO;
}


- (id)transformedValue:(id)beforeObject{
	
	
	if (beforeObject == nil) return nil;
	
	
	switch([beforeObject intValue]){
		
		case 0:
		case 28:
		case 29:
			return [[NSNumber alloc] initWithBool:NO];
		default:
			return [[NSNumber alloc] initWithBool:YES];

	}
}

@end
