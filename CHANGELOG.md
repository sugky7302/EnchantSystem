# CHANGELOG

## 0.1.1.11 - 2021-05-22

### Todo:
- [x] How to load data from the database.
- [x] The output of database needs to change coding.
- [x] Finish Attribute.
- [x] Finish AttributeTree.
- [x] Finish Rune.
- [x] Finish Equipment.
- [ ] Rewrite red-black tree

### added:
- Add a database "attribute.sqlite3".
- Add a database "drop.sqlite3".
- [CMakeLists.txt]
  - Add the include path of red black tree, we can use in the cpp now.
  - Add the include path of sqlite3.
  - Add the include path of json.
- [equipment.cpp]
  - Complement all class.
  - Attribute adds 6 methods.
  - Attribute can load data from attribute.sqlite3.
  - Let database name be modified from class Attribute, not in the constructor.
  - When we set value, attribute's text is changed synchronously.
  - Finish AttributeTree imcomplement.
- [equipment.h] 
    - Attribute adds 6 methods.
        - getId can get the attribute number.
        - getName can get the attribute name.
        - getText can get the attribute description.
        - getValue can get the attribute value.
        - setValue can set the attribute value and text is changed synchronously.
        - callback is used to the sqlite3_exec callback.
    - Add Equipment's type.
- [include/] Add database.h and drop.h.
- [lib/] Add json thirdparty.
- [src/] Add drop.cpp and finish DropItem system.
- [main.cpp] 
  - Test whether all class take some mistakes.
  - Add sqlite3 header.
  - Add drop header.
  - Add database header.

### Changed:
- [CMakeLists.txt] We no longer add the included path of thirdparty everytime.
- [equipment.h] Adjust definitions and params of all class, some params provide default value to simplify using step.

## 0.1.0.0 - 2021-04-08 - First Commit
- Finish CMake setting.
- Finish Clang Formatter setting.
- Successly build and run. 