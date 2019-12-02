//
//  MKEglRender.h
//  Pods
//
//  Created by xiewei on 2019/11/26.
//

#import <UIKit/UIKit.h>

@interface MKEglRender : NSObject

- (int)open;
- (void)close;

- (void)setView:(UIView*)view
       toStream:(NSString*)streamId;

- (void)updateFrame:(CVPixelBufferRef)buffer
       withRotation:(int)roation
           toStream:(NSString*)streamId;

@end
