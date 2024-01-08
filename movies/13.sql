SELECT DISTINCT
  p.name
FROM
  people p
  JOIN stars s ON s.person_id = p.id
  JOIN movies m ON s.movie_id = m.id
WHERE
  m.id IN (
    SELECT DISTINCT
      m2.id
    FROM
      people p2
      JOIN stars s2 ON s2.person_id = p2.id
      JOIN movies m2 ON s2.movie_id = m2.id
    WHERE
      p2.name = 'Kevin Bacon'
      AND p2.birth = 1958
  )
  AND p.name != 'Kevin Bacon';