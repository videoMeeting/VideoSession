

#import <UIKit/UIKit.h>

@interface ChatCustomCell : UITableViewCell{
	UILabel      *dateLabel;
	UIButton     *deleteButton;
}
@property (nonatomic, retain) IBOutlet UIButton     *deleteButton;
@property (nonatomic, retain) IBOutlet UILabel      *dateLabel;

@end
