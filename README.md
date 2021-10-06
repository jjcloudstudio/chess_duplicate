# Mocking
This exercise is intended to give you some experience with creating mocks using Gmock.

# Instructions
1. Fork the project at http://gitlab.cs.uleth.ca/course3720/lecture-exercises/mocking
    * The project contains two classes:
	    * Door - represents a door in the house. This will be the class that is mocked.
		* House - represents a house with a dog in it that wants to be let out.
1. Create a local clone of your repo.
1. Create a test case that:
	* Mocks the Door
	* Creates a House with the mocked Door
	* Verifies the following about the dogOut() method:
	    * The door is only unlocked, opened, closed, and locked once respectively.
		* A door is unlocked before it is opened.
		* A door is closed after it is opened.
		* A door is locked after it is closed.
		* The dog is outside after dogOut() is called (this is state test, the type of test you have done before)
1. Subclasses of House are provided that have different errors in the dogOut() method. See how your test fails by:
	* Copying your test method
	* Rename it
	* Change the created object from House to one of the subclasses.

# Notes
1. You may want to look at the Warehouse example at http://gitlab.cs.uleth.ca/course3720/examples/Examples/WarehouseMock
1. The `test` branch contains a solution that you can refer to if you get really stuck and need extra help. But try your best to figure this out on your own - you'll learn more that way. 
