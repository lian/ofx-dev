#import "PreferenceWindow.h"

@implementation PreferenceWindow

- (IBAction)cancel:(id)sender
{
	[NSApp endSheet:self returnCode:0];
	
}

- (IBAction)ok:(id)sender
{
	[NSApp endSheet:self returnCode:1];
	
}

@end
