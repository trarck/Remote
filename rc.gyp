{
  'targets': [
  {
          'target_name': 'libDevice',
          'type': 'static_library',          
          'defines':[
            
          ],

          'include_dirs': [
            'src/device',
          ],
          'sources': [
            'src/device/Input.h',
            'src/device/FrameBuffer.h',
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
             ['yh_library=="static_library"',{
                  'defines':['YH_STATIC'],
                }
             ],
             ['yh_library=="shared_library"',{
                  'defines':['YH_USRDLL'],                  
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
          'target_name': 'libyh',
          'type': '<(yh_library)',
          
          'defines':[
            'SQLITE_HAS_CODEC'
          ],

          'include_dirs': [
            'yh/',
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
             ['yh_library=="static_library"',{
                  'defines':['YH_STATIC'],
                }
             ],
             ['yh_library=="shared_library"',{
                  'defines':['YH_USRDLL'],                  
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
      }
  ]
}