import java.util.Scanner;

public class Main {

	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		String str = scan.nextLine();
		scan.close();
		CalcExpression a = new CalcExpression();
		int ans = a.Calculate(str);
		System.out.println(ans);
	}

}
