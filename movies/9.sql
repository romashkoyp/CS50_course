SELECT
  people.name
FROM
  stars
  JOIN people ON stars.person_id = people.id
  JOIN movies ON stars.movie_id = movies.id
WHERE
  movies.year = 2004
GROUP BY
  people.name,
  people.birth
ORDER BY
  people.birth