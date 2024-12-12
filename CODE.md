# Code

Based in guides like Google C++ Style Guide, and Unreal Engine Coding Standard and LLVM Coding Standards.

## Style

- Always use a tab for indentation (a tab is equal to 4 spaces).
- Class names should be in PascalCase.
- Function names should be in PascalCase.
- Variable names should be in camelCase.
- Constants should be in SCREAMING_SNAKE_CASE.
- Class member variables should be prefixed with an m_and start with an uppercase letter. eg: m_Level.
- If a class member variable is a boolean, it should start with is, eg: m_IsAlive.
- If a class function returns a reference, it should be named as the variable, eg: Level().
- Instead, if a class function returns a copy, it should be named as a verb, eg: GetLevel().
- Use the override keyword when overriding a virtual function.
- Use the final keyword when a function should not be overridden.
- Use the delete keyword when a function should not be used.
- Use the types provided by Poltergeist whenever possible.
- AVOID use macros.
- AVOID use raw pointers.
