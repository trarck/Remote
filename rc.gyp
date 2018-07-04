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
            'src/device/Define.h',
            'src/device/InputDevice.h',
            'src/device/InputManager.h',
            'src/device/InputManager.cpp',            
          ],
          'conditions': [
              ['OS=="win"', {
                  'defines': [
                    'WIN32','_WINDOWS'
                  ],
                  'sources': [
                    'src/device/win/Define-win.h',
                    'src/device/win/InputDevice.cpp',
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
                    'src/device/unix/InputDevice.cpp',
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