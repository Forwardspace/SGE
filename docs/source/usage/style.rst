Style Guide
===========

We have STANDARDS here! To better understand existing code and contribute by adding new code, please follow the simple style guide below.

Brackets/Parentheses
--------------------
The opening bracket is placed on the same line as the expression requiring it.

Example:
::
	if (foo == bar) {
		...
	}

	class FooBar {
		...
	};

Variable naming
---------------

Generally, variables are named using *camelCase*.
Private variables have an underscore after their name if they have externally available getters/setters.

Example:
::
	int fooBar = 3;

	class ... {
		int fooBar_ = 3;
		...
	};

Classes
-------

Classes use *PascalCase*.
The ``private:`` and ``public:`` labels in classes are inline with the ``class`` declaration.

It is also worth mentioning that each important class should have its own .cpp and .h files.

Example:
::
	class FooBarManager {
	public:
		...
	private:
		...
	};

Enums
-----

All enums are declared inside a namespace with the enum's name under an enum named ``Enum``.

Example:
::
	//enum Foo
	namespace Foo {
		enum Enum {
			FOO,
			BAR
		};
	}

	//To use it
	Foo::Enum bar = Foo::BAR;

This is done to avoid polluting the surrounding namespaces.

---------------------------------------

Ultimately, just follow the existing style and everything will be fine.