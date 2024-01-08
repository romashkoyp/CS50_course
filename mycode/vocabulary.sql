-- Looking for equal verbs with different endings (2 letters in the end)
SELECT DISTINCT sana FROM mytable
WHERE typpi = 'verbi'
AND sana LIKE '%ua'
OR sana LIKE '%aa'
ORDER BY LENGTH(sana) ASC, sana ASC;

SELECT DISTINCT m1.sana AS similar_verbs
FROM mytable m1
INNER JOIN mytable m2
ON LENGTH(m1.sana) = LENGTH(m2.sana)
AND m1.typpi = 'verbi'
AND m2.typpi = 'verbi'
AND m1.sana <> m2.sana
AND SUBSTR(m1.sana, 1, LENGTH(m1.sana) - 2) = SUBSTR(m2.sana, 1, LENGTH(m2.sana) - 2)
ORDER BY LENGTH(m1.sana) ASC, m1.sana ASC;

-- Looking for nouns -aa/ää type
SELECT DISTINCT sana FROM mytable
WHERE typpi = 'substantiivi'
AND sana LIKE '%aa' OR sana LIKE '%ää'
ORDER BY LENGTH(sana) ASC, sana ASC;

-- Looking for nouns with 3 letters only
SELECT DISTINCT sana FROM mytable
WHERE typpi = 'substantiivi'
AND LENGTH(sana) = 3
AND sana NOT REGEXP '^[aäeioöuyAÄEIOÖUY].*$'
AND SUBSTRING(sana, 2, 1) NOT REGEXP '^[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ]$'
AND SUBSTRING(sana, 3, 1) NOT REGEXP '^[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ]$'
ORDER BY sana ASC;

-- Looking for nouns with -sto in the end
SELECT DISTINCT sana FROM mytable
WHERE typpi = 'substantiivi'
AND sana LIKE '%sto'
ORDER BY LENGTH(sana) ASC, sana ASC;

-- Looking for adjectives with -is in the end
SELECT DISTINCT sana FROM mytable
WHERE typpi = 'adjektiivi'
AND sana LIKE '%is'
ORDER BY LENGTH(sana) ASC, sana ASC;