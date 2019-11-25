//
//  ViewController.m
//  MediaKitDemo
//
//  Created by xiewei on 2019/5/28.
//  Copyright © 2019 xiewei. All rights reserved.
//

#import "ViewController.h"
#include "manager/mediakit_manager.h"
#include "thread_test.h"
#include "video/video_render_egl.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
//    mk::MediaKitManager* manager = new mk::MediaKitManager();
//    manager->init();
//    ThreadTest* test = new ThreadTest();
//    test->func1();
    mk::VideoRenderEGL* v = new VideoRenderEGL();
    v->setRenderInterval(2000);
    v->open();
}


@end
