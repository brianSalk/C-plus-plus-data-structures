#pragma once
namespace briguy
{
	class OutOfBoundsException
	{
	public:
		OutOfBoundsException() {}
		OutOfBoundsException(long int i) : index(i) {}
		long int getIndex() { return index; }
	private:
		long int index;
	};
}

