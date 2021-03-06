import unittest

from pystan import stanc, StanModel
from pystan._compat import PY2


class TestStanc(unittest.TestCase):

    def test_stanc(self):
        model_code = 'parameters {real y;} model {y ~ normal(0,1);}'
        result = stanc(model_code=model_code)
        assert sorted(result.keys()) == sorted({"status", "model_cppname",
                                                "cppcode", "model_name",
                                                "model_code"})
        assert result['cppcode'].startswith("// Code generated by Stan ")
        self.assertEqual(result['status'], 0)

    def test_stanc_exception(self):
        model_code = 'parameters {real z;} model {z ~ no_such_distribution();}'
        assertRaisesRegex = self.assertRaisesRegexp if PY2 else self.assertRaisesRegex
        with assertRaisesRegex(ValueError, 'unknown distribution'):
            stanc(model_code=model_code)
        with assertRaisesRegex(ValueError, 'unknown distribution'):
            StanModel(model_code=model_code)

    def test_stanc_exception_semicolon(self):
        model_code = """
        parameters {
            real z
            real y
        }
        model {
            z ~ normal(0, 1);
            y ~ normal(0, 1);}
        """
        assertRaisesRegex = self.assertRaisesRegexp if PY2 else self.assertRaisesRegex
        with assertRaisesRegex(ValueError, 'EXPECTED: ";" BUT FOUND'):
            stanc(model_code=model_code)
        with assertRaisesRegex(ValueError, 'EXPECTED: ";" BUT FOUND'):
            StanModel(model_code=model_code)
