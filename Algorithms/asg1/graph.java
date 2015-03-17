// Figure A.1

#import	scanner

public
class	graph
	{
	public static
	void	main(String[] argv)
		{
		int	m, n;
		IntList[]	adjVertices;

		if (argv.length == 0)
			{
			System.out.println("Usage: java graph input.data");
			System.exit(0);
			}
		String	infile = argv[0];
		BufferedReader	inbuf = InputLib.fopen(infile);
		System.out.println("Opened " + infile + " for input.");
		String	line = InputLib.getLine(inbuf);
		n = LoadGraph.parseN(line);
		System.out.println("n = " + n);

		}

	}

