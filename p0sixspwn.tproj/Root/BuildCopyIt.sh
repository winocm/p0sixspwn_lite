xcrun -sdk iphoneos clang CopyIt.c -o CopyIt -arch armv7
codesign -s- CopyIt
