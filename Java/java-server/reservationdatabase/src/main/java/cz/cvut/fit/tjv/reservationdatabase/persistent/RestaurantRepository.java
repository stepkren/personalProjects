package cz.cvut.fit.tjv.reservationdatabase.persistent;

import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface RestaurantRepository extends JpaRepository<Restaurant, Long> {
    public Restaurant findRestaurantByName(String name);
}
