pip uninstall pycgal -y
rm build -rf
rm dist -rf
rm pycgal.egg-info -rf
python setup.py install
python tests/test.py