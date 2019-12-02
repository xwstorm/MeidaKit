#
# Be sure to run 'pod lib lint ByteRtcEngineKit.podspec' to ensure this is a
# valid spec before submitting.
#
Pod::Spec.new do |s|
  s.name             = 'MediaKitSrc'
  s.version          = '1.1'
  s.summary          = 'MediaKit is a media library.'
  s.description      = 'MediaKit is a media tools library.'
  s.homepage         = 'https://github.com/xwstorm/MediaKit'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'xiewei' => 'xiew' }
  s.source           = { :git => 'https://github.com/xwstorm/MediaKit.git', :branch => 'master' }
  s.xcconfig         = {'HEADER_SEARCH_PATHS'  => '"${PODS_ROOT}/../../../" "${PODS_ROOT}/../MediaKit/sdk" "${PODS_ROOT}/../MediaKit"', 'GCC_PREPROCESSOR_DEFINITIONS' => 'MK_IOS=1'}
  s.ios.deployment_target = '8.0'
  s.source_files     =  [
    'base/**/*.{h,cpp,mm}',
    'video/**/*.{h,cpp,mm}',
    'sdk/**/*.{h,cpp,mm}',
  ]
end
