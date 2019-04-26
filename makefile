catracas:
	@ g++ cadastro.cpp -lcurl
	@ ./a.out

servidor:
	@ export FLASK_APP=run.py
	@ flask run

clean:
	@ rm *.out *.pyc || true
