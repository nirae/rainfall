class N {
	char *string;
	int number;

	// constructeur
	N(int number) {
		this->number = number;
	}

	void setAnnotation(char *str) {
	  size_t len;

	  len = strlen(param_1);
	  // memcpy(this + 4, str, len);
	  // The overflow is here
	  memcpy(this->string, str, len);
	  return;
	}
};

int main(int ac,char **av) {
	N nclass_1;
	N nclass_2;
	int iVar1;

	if (ac < 2) {
		exit(1);
	}

	nclass_1 = new N(5);
	nclass_2 = new N(6);

	nclass_1.setAnnotation(av[1]);
	iVar1 = (***nclass_2)(nclass_2, nclass_1); // ???
	return iVar1;
}
