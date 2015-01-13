//
//  EditGroupViewController.m
//  VideoSession
//
//  Created by zhangxm on 13-3-16.
//  Copyright (c) 2013年 zhangxm. All rights reserved.
//

#import "EditGroupViewController.h"
#import "HandInputViewController.h"
#import "GroupsViewController.h"
@interface EditGroupViewController ()

@end

@implementation EditGroupViewController
@synthesize toolBar;
@synthesize groupName;
@synthesize handInputViewController;
@synthesize groupsViewController;
@synthesize oldgroupname;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
-(IBAction)BtExit:(id)sender
{
    self.hidesBottomBarWhenPushed = YES;
    [self.navigationController popViewControllerAnimated:YES];
    self.hidesBottomBarWhenPushed = NO;
}
-(IBAction)btSave:(id)sender
{
    if([self.groupName.text isEqualToString:@""])
    {
        [self Alert:@"组名不能为空" message:@"请输入组名"];
        return;
    }
    
    if([self.groupName.text isEqualToString:oldgroupname])
    {
        self.hidesBottomBarWhenPushed = YES;
        [self.navigationController popViewControllerAnimated:YES];
        self.hidesBottomBarWhenPushed = NO;
        return;
    }
    
    std::string strGropName = [self.groupName.text UTF8String];
    int re = pLoginServer->UserGropUpdateName([self.oldgroupname UTF8String],strGropName);
    if(re == -2)
    {
        [self Alert:@"更改后的组已经存在" message:@"请输入其它组名"];
        return;
    }
    self.hidesBottomBarWhenPushed = YES;
    [self.navigationController popViewControllerAnimated:YES];
    self.hidesBottomBarWhenPushed = NO;
}

-(void)Alert:(NSString*) result message:(NSString*) message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:result message:message
                                                   delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil];
    [alert show];
    [alert release];
}

-(void)HandInputPressed:(id)sender
{
    self.handInputViewController=[[[HandInputViewController alloc]initWithNibName:@"HandInputViewController" bundle:nil]autorelease];
    self.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:self.handInputViewController animated:YES];
    self.handInputViewController.groupname = self.groupName.text;
   // self.hidesBottomBarWhenPushed = NO;
}

-(IBAction)ExistGroupPressed:(id)sender
{
    self.groupsViewController=[[[GroupsViewController alloc]initWithNibName:@"GroupsViewController" bundle:nil]autorelease];
    //self.groupsViewController.tableview sett
    self.groupsViewController.savegroupname = self.groupName.text;
    self.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:self.groupsViewController animated:YES];
    //self.hidesBottomBarWhenPushed = NO;
}
- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    UIBarButtonItem *leftBtn = [[UIBarButtonItem alloc]initWithTitle:@"取消" style:UIBarButtonItemStyleBordered target:self action:@selector(BtExit:)];
    self.title=@"编辑群组";
    self.navigationItem.leftBarButtonItem = leftBtn;
    [leftBtn release];
    
    UIBarButtonItem *rightBtn = [[UIBarButtonItem alloc]initWithTitle:@"保存" style:UIBarButtonItemStyleBordered target:self action:@selector(btSave:)];
    self.navigationItem.rightBarButtonItem = rightBtn;
    [rightBtn release];
    
    UIBarButtonItem *HandInputItem = [[UIBarButtonItem alloc]initWithTitle:@"手动输入" style:UIBarButtonItemStyleBordered target:self action:@selector(HandInputPressed:)];
    UIBarButtonItem *ExistGroupItem = [[UIBarButtonItem alloc]initWithTitle:@"现有群组" style:UIBarButtonItemStyleBordered target:self action:@selector(ExistGroupPressed:)];
    
    UIBarButtonItem *flexibleSpace = [[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil]autorelease]; //占位置，空格
    NSArray *items = [NSArray arrayWithObjects:HandInputItem ,flexibleSpace,ExistGroupItem,nil];
    
    [self.toolBar setItems:items animated:NO];
    pLoginServer = LoginServer::OnGetLoginServer();
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

-(void)dealloc
{
    pLoginServer=NULL;
    self.toolBar=nil;
    self.groupName=nil;
    self.handInputViewController=nil;
    self.groupsViewController=nil;
    [super dealloc]; 
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
