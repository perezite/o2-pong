namespace v1
{
	template <class T>
	struct Vector2 
	{
		T x, y;

	public:
		inline Vector2() : x(T()), y(T())
		{ }

		inline Vector2(const T& s) : x(s), y(s) 
		{ }

		inline Vector2(const T& x_, const T& y_) : x(x_), y(y_)
		{ }
	};

	typedef Vector2<int> Vector2i;
}