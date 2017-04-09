# AutoRobo_Cpp
__Rewrite of AutoRobo project in C++__

Main purpose of this re-write is to have code that is easy to test - in original project it was offten a pain. For this task I created minimal unit test framework for Stm32F4xx, which made testing much easier than debugging some test functions scattered throughout the code.

I try TDD here - write class interface, unit tests for this interface and if most important functionality is test-covered go on with implementation. So far it goes well.
