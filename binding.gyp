{
  "targets": [
    {
      "target_name": "bitcoinconsensus",
      "variables": {
        "with_gmp%": "<!(./utils/has_lib.sh bitcoinconsensus)"
      },
      "sources": [ 
        "./src/bitcoinconsensus.cc" 
      ],
      "link_settings": {
          "libraries": [
              "-lbitcoinconsensus"
          ]
      },
      "include_dirs": [
          "/usr/local/include",
          "<!(node -e \"require('nan')\")"
      ],

    }
  ]
}
