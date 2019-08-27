import java.util.ArrayList;
import java.util.Stack;

public class CalcExpression 
{
	private static final int PriorityBracket = 10;
	private static final int PriorityAdd = 1;
	private static final int PriorityMinus = 1;
	private static final int PriorityMultiply = 2;
	private static final int PriorityDivide = 2;
	private static final int PriorityMod = 2;
	
	public CalcExpression()
	{

	}
	
	private boolean IsAddOrMinus(char c)
	{
		return c=='+' || c=='-';
	}
	
	private boolean IsArithmeticOperator(char c)
	{
		return IsAddOrMinus(c) || c=='*' || c=='/' || c=='%';
	}
	
	private boolean IsNumberOperator(char c)
	{
		return IsArithmeticOperator(c) || c=='(' || c==')';
	}
	
	private ArrayList<String> SplitIntoArrayList(final String s)
	{
		ArrayList<String> MySplit = new ArrayList<String>();
		int i = 0;
		MySplit.add("(");
		while(i<s.length())
		{
			char NowChar = s.charAt(i);
			StringBuffer StrBuf = new StringBuffer();
			if(Character.isDigit(NowChar)==true)
			{
				do
				{
					StrBuf.append(NowChar);
					i++;
					if(i>=s.length())break;
					NowChar = s.charAt(i);
				}while(Character.isDigit(NowChar)==true);
				MySplit.add(StrBuf.toString());
			}
			else if(IsNumberOperator(NowChar)==true)
			{
				StrBuf.append(NowChar);
				i++;
				if(IsAddOrMinus(NowChar))
				{
					char LastStrC = MySplit.get(MySplit.size()-1).charAt(0);
					if(IsArithmeticOperator(LastStrC) || LastStrC == '(')
					{
						MySplit.add("0");
					}
				}
				MySplit.add(StrBuf.toString());
			}
			else if(NowChar==' ')i++;
			else throw new ArithmeticException();
		}
		MySplit.add(")");
		
		int CountLeftBracket = 0,CountRightBracker = 0;
		for(int tp=0;tp<MySplit.size();tp++)
		{
			char chr1 = MySplit.get(tp).charAt(0);
			if(chr1 == '(')
			{
				CountLeftBracket++;
			}
			else if((chr1 == ')'))
			{
				CountRightBracker++;
				if(CountRightBracker > CountLeftBracket)
				{
					throw new ArithmeticException();
				}
			}
		}
		
		if(CountLeftBracket != CountRightBracker)
		{
			throw new ArithmeticException();
		}
		
		for(int tp=0;tp<MySplit.size()-1;tp++)
		{
			char chr1 = MySplit.get(tp).charAt(0);
			char chr2 = MySplit.get(tp+1).charAt(0);
			if(Character.isDigit(chr1) && Character.isDigit(chr2))
			{
				throw new ArithmeticException();
			}
		}
		return MySplit;
	}
	
	private int evaluate(char Oper,int first,int second) throws ArithmeticException
	{
		switch(Oper)
		{
		case '+':
			return first + second;
		case '-':
			return first - second;
		case '*':
			return first * second;
		case '/':
			return first / second;
		case '%':
			return first % second;
		default:
			throw new ArithmeticException();
		}
	}
	
	private int GetPriority(char Oper,int CountLeftBracket)
	{
		switch(Oper)
		{
		case '+':
			return CountLeftBracket * PriorityBracket + PriorityAdd;
		case '-':
			return CountLeftBracket * PriorityBracket + PriorityMinus;
		case '*':
			return CountLeftBracket * PriorityBracket + PriorityMultiply;
		case '/':
			return CountLeftBracket * PriorityBracket + PriorityDivide;
		case '%':
			return CountLeftBracket * PriorityBracket + PriorityMod;
		case ')':
			return CountLeftBracket * PriorityBracket;
		default:
			throw new ArithmeticException();
		}
	}
	
	public int Calculate(final String s)
	{
		final ArrayList<String> MySplit = SplitIntoArrayList(s);
		Stack<Integer> nums = new Stack<Integer>();
		Stack<Pair<Character,Integer>> oper = new Stack<Pair<Character,Integer>>();
		int CountLeftBracket = 0,i = 0,LastOperPriority = 0;
		
		while(i<MySplit.size())
		{
			String NowStr = MySplit.get(i++);
			char NowChar = NowStr.charAt(0);
			if(NowChar == '(')
			{
				CountLeftBracket++;
			}
			else if(Character.isDigit(NowChar))
			{
				int TmpNum = Integer.parseInt(NowStr);
				nums.push(TmpNum);
			}
			else if(IsNumberOperator(NowChar))
			{
				final int NowPriority = GetPriority(NowChar,CountLeftBracket);
				LastOperPriority = (oper.isEmpty())?(0):oper.peek().GetSecond();
				while(LastOperPriority >= NowPriority)
				{
					try
					{
						Pair<Character,Integer> NowOperPair = oper.pop();
						LastOperPriority = (oper.isEmpty())?(0):oper.peek().GetSecond();
						char NowOper = NowOperPair.GetFirst();
						int SecondNum = nums.pop();
						int FirstNum = nums.pop();
						Integer ans = evaluate(NowOper,FirstNum,SecondNum);
						nums.add(ans);
					}
					catch(java.util.EmptyStackException e)
					{
						throw new ArithmeticException();
					}
				}
				if(NowChar == ')')
				{
					CountLeftBracket--;
					if(CountLeftBracket < 0)
						throw new ArithmeticException();
				}
				else
				{
					oper.push(new Pair<Character,Integer>(NowChar,NowPriority));
				}
			}
			else throw new ArithmeticException();
		}
		if(nums.size()!=1 || CountLeftBracket!=0 || !oper.isEmpty())throw new ArithmeticException();
		return nums.peek();
	}
}
