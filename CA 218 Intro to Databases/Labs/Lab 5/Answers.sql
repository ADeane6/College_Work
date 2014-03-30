select name, population 
from Country 
where name = "Netherlands";


select District, round(avg(population),0) as Average 
from City 
where countrycode = (select code from Country where name = "Netherlands") 
group by District;

select Name, HeadOfState, population 
from Country 
where population > 10000000 
order by Population desc;

select Name, population
from Country
Where Continent = "Africa" and LifeExpectancy > 60
group by population;

select Name, population
from Country
Where Continent = "Europe" and Code in 
(select countrycode from City group by countrycode having count(district) > 10);

select 