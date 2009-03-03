/***********************************************************************
 
 Copyright (c) 2009, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/


#import <UIKit/UIKit.h>


@interface MSARootViewController : UIViewController <UIActionSheetDelegate, UIScrollViewDelegate> {
	IBOutlet UIBarButtonItem			*saveButton;
	IBOutlet UIActivityIndicatorView	*activityIndicator;
	
	IBOutlet UIView						*infoView;

	IBOutlet UIScrollView				*scrollView;
	IBOutlet UIPageControl				*pageControl;
	IBOutlet UIViewController			*optionsViewController;
	
	bool _isOn;
	bool pageControlUsed;
}

@property (readonly) UIViewController *optionsViewController;

-(void)addPage:(UIView*)view;
-(IBAction)nextPage:(id)sender;
-(IBAction)prevPage:(id)sender;

-(void) openView:(bool)animate;
-(IBAction) closeView:(id)sender;
-(bool) isOn;


-(IBAction) savePhoto:(id)sender;
-(void) saveComplete;
-(IBAction) pageChanged:(id)sender;
-(void) updatePages;

@end
