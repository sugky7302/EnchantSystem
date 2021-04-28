# CHANGELOG


## 0.1.1.3 - 2021-04-09

### Todo:
- [x] How to load data from the database.
- [x] the output of database needs to change coding.
- [ ] rewrite red-black tree

### added:
- [CMakeLists.txt]
  - Add the include path of red black tree, we can use in the cpp now.
  - Add the includ path of sqlite3.
- [equipment.cpp]
  - Complement all class.
  - Attribute adds two methods.
  - Attribute can load data from attribute.sqlite3.
- [equipment.h] Attribute adds two methods. getName can get the attribute name and getText can get the attribute description.
- [main.cpp] 
  - Test whether all class take some mistakes.
  - Add sqlite3 header.

### Changed:
- [equipment.h] Adjust definitions and params of all class, some params provide default value to simplify using step.

## 0.1.0.0 - 2021-04-08 - First Commit
- Finish CMake setting.
- Finish Clang Formatter setting.
- Successly build and run. 