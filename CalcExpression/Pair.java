
public class Pair<A,B> 
{
	private final A _first;
	private final B _second;
	public Pair(A first,B second)
	{
		_first = first;
		_second = second;
	}
	
	public A GetFirst()
	{
		return _first;
	}
	
	public B GetSecond()
	{
		return _second;
	}
	
	@Override
	public String toString()
	{
		return "("+_first.toString()+","+_second.toString()+")";
	}
}
