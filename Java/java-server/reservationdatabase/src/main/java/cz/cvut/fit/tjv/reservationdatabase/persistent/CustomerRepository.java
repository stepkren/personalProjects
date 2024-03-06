package cz.cvut.fit.tjv.reservationdatabase.persistent;

import cz.cvut.fit.tjv.reservationdatabase.domain.Cuisine;
import cz.cvut.fit.tjv.reservationdatabase.domain.Customer;
import cz.cvut.fit.tjv.reservationdatabase.domain.Restaurant;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface CustomerRepository extends JpaRepository<Customer, Long> {
    @Query(value = "SELECT DISTINCT c FROM Customer c JOIN c.visited v JOIN v.cooks r WHERE r = :cuisine")
    public List<Customer> findCustomerThatVisitedRestaurantCookingCuisine(@Param("cuisine") Cuisine cuisine);

    public Customer findCustomerByName (String name);
}
