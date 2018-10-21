# Greenhouse Climate Controller
In this Greenhouse Climate controller we are using *Fuzzy logic algorithms* to set the actuators for a variable output.'

## FuZZy Logic 
* Traditional Algorithms understand only 0s and 1s but the fuzzy logic would we in between 0-1 which will increase the precision of the whole control system.
* Since, Handling Greenhouse climate is a complex task we would require such kind of algorithms to reduce the mathematical complexity of the system to work with less power.
* Fuzzy logic is an approach to computing based on "degrees of truth" rather than the usual "true or false" (1 or 0) Boolean logic on which the modern computer is based.

#### [FuZZy_Logic](https://github.com/zerokol/eFLL) : This logic has been adopted by the kisted website.


## Brief Documentation on FuZZy Logic

_PARA MAIORES INFORMAÇÕES VISITE OS LINKS NO TOPO_

_FOR MORE INFORMATIONS VISITE THE LINKS ON THE TOP_

**Fuzzy object** - This object includes all the Fuzzy System, through it, you can manipulate the Fuzzy Sets, Linguistic Rules, inputs and outputs.

**FuzzyInput** object - This object groups all entries Fuzzy Sets that belongs to the same domain.

**FuzzyOutput** object - This object is similar to FuzzyInput, is used to group all output Fuzzy Sets thar belongs to the same domain.

**FuzzySet** object - This is one of the main objects of Fuzzy Library, with each set is possible to model the system in question. Currently the library supports triangular membership functions, trapezoidal and singleton, which are assembled based on points A, B, C and D, they are passed by parameter in its constructor FuzzySet(float a, float b, float c, float d).

**FuzzyRule** object - This object is used to mount the base rule of Fuzzy object, which contains one or more of this object. Instantiated with FuzzyRule fr = new FuzzyRule (ID, antecedent, consequent).

**FuzzyRuleAntecedent** object - This object is used to compound the object FuzzyRule, responsible for assembling the antecedent of the conditional expression of a FuzzyRule.

**FuzzyRuleConsequente** object - This object is used to render the object FuzzyRule, responsible for assembling the output expression of a FuzzyRule.
