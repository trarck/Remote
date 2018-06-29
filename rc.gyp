{
  'targets': [
        {
          'target_name': 'libDevice',
          'type': 'static_library',          
          'defines':[
            
          ],

          'include_dirs': [
            'deps/yh/include',
            'src/device',
          ],
          'sources': [
            'src/device/DeviceMacros.h',
            'src/device/Device.h',
            'src/device/DeviceManager.h',
            'src/device/DeviceManager.cpp',            
          ],
          'conditions': [
              ['OS=="win"', {
                  'defines': [
                    'WIN32','_WINDOWS'
                  ],
                  'sources': [
                    'src/device/win/Define.h',
                    'src/device/win/Device.cpp',
                  ]
                }
             ],
             ['OS=="mac"', {
                  'defines': [

                  ],
                  'sources': [
                    'src/device/unix/Device.cpp',
                  ]
                }
             ],

             ['OS=="ios"', {
                  'defines': [

                  ],
                  'sources': [
                    'src/device/unix/Device.cpp',
                  ]
                }
             ],
             ['OS=="android"', {
                  'defines': [

                  ],
                  'sources': [
                    'src/device/unix/Device.cpp',
                  ]
                }
             ],
             ['OS=="linux"', {
                  'defines': [

                  ],
                  'sources': [
                    'src/device/unix/Device.cpp',
                  ]
                }
             ],
             ['OS=="winrt"', {
                  'defines': [

                  ],
                  'sources': [

                  ]
                }
             ],
             #['OS=="win" and yh_library=="shared_library"', {
             #     'defines': [
             #       'SQLITE_API=__declspec(dllexport)'
             #     ]
             #   }
             #]
         ],
         'configurations': {
            'Debug': {
                'defines': [ 'YH_USE_SCRIPT_LOG','YH_DEBUG'],
            },
			'Release': {
                'defines': ['NODEBUG'],
            }
         },
      },
      
      {
          'target_name': 'rc',
          'type': 'executable',
          
          'defines':[
            
          ],

          'include_dirs': [
            'src',
            'src/device'            
          ],
          'sources': [
            
            
          ],
          'conditions': [
              ['OS=="win"', {
                  'defines': [
                    'WIN32','_WINDOWS'
                  ],
                  'sources': [
  
                  ]
                }
             ],
             ['OS=="mac"', {
                  'defines': [

                  ],
                  'sources': [
   
                  ]
                }
             ],

             ['OS=="ios"', {
                  'defines': [

                  ],
                  'sources': [

                  ]
                }
             ],
             ['OS=="android"', {
                  'defines': [

                  ],
                  'sources': [

                  ]
                }
             ],
             ['OS=="linux"', {
                  'defines': [

                  ],
                  'sources': [

                  ]
                }
             ],
             ['OS=="winrt"', {
                  'defines': [

                  ],
                  'sources': [

                  ]
                }
             ],            
         ],
         'configurations': {
            'Debug': {
                'defines': [ 'YH_USE_SCRIPT_LOG','YH_DEBUG'],
            },
			'Release': {
                'defines': ['NODEBUG'],
            }
         },
      }
  ]
}