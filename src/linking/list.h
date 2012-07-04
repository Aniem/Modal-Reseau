namespace Modal{
	class List {
		public:
		List();
		List(int n,List* l);
		~List();
		int value();
		List* next();
		bool isEmpty();
		int setvalue(int n);
		protected:
			int v;
			List* n;
			int vide;
	};
}
