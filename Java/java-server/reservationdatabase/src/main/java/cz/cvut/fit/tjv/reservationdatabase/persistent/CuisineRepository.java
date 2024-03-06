package cz.cvut.fit.tjv.reservationdatabase.persistent;

import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface CuisineRepository extends JpaRepository<Cuisine, Long> {
    public Cuisine findCuisineByCountry (String country);
}
