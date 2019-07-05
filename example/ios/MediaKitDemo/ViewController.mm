//
//  ViewController.m
//  MediaKitDemo
//
//  Created by xiewei on 2019/5/28.
//  Copyright © 2019 xiewei. All rights reserved.
//

#import "ViewController.h"
#include "manager/mediakit_manager.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    mk::MediaKitManager* manager = new mk::MediaKitManager();
    manager->init();
}


@end
