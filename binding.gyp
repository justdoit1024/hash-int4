{
  "targets": [
    {
      "target_name": "hashint4",
      "sources": [ "addon_hashint4.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
