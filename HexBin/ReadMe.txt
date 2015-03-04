Small GUI tool to convert hex/binary

Building installer:
install WiX http://wix.codeplex.com
Edit installer.wxs , update the version. Generate new GUIDs for:
  UpgradeCode and ProductCode
run the build_installer.bat