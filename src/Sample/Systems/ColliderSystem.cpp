#include "ColliderSystem.h"

bool inline lineColliding(float xa1, float xa2, float xb1, float xb2){
    return xa2 > xb1 && xa1 < xb2;
}
bool inline nearZero(float x, float precision=0.5f){
    return x < precision && x > -precision;
}
bool inline boxColliding(float xa1, float xa2, float ya1, float ya2, float xb1, float xb2, float yb1, float yb2){
    return (ya2 > yb1 && ya1 < yb2 && xa2 > xb1 && xa1 < xb2);
}

void ColliderSystem::OnUpdate(float t) {

    for (auto& id1: _moveStorage.Entities())
    {
        if (!world.IsEntityAlive(id1))
            continue;
        if (!_colliderStorage.Has(id1))
            continue;

        auto& move1 = _moveStorage[id1];
        auto& pos1 = _posStorage[id1].pos;
        auto& coll1 = _colliderStorage[id1];
        
        // стремное выражение - смещение от центра; //bbx1<bbx2, bby1 < bby2
        float bb1x1 = pos1.x - (((coll1.w>_gridSize)? _gridSize : coll1.w) / 2.f);       
        float bb1x2 = bb1x1 + coll1.w;                                                    
        
        float bb1y2 = pos1.y + (((coll1.h>_gridSize)? _gridSize : coll1.h) / 2.f);
        float bb1y1 = bb1y2 - coll1.h;

        for (auto& id2: _colliderStorage.Entities())
        {
            if (!world.IsEntityAlive(id2))
                continue;
            if (id1 == id2)
                continue;
            
            auto& pos2 = _posStorage[id2].pos;
            auto& coll2 = _colliderStorage[id2];
            
            float bb2x1 = pos2.x - (((coll2.w>_gridSize)? _gridSize : coll2.w) / 2.f);       
            float bb2x2 = bb2x1 + coll2.w;                                                    
            
            float bb2y2 = pos2.y + (((coll2.h>_gridSize)? _gridSize : coll2.h) / 2.f);
            float bb2y1 = bb2y2 - coll2.h;
            
            if (boxColliding(
                bb1x1 + move1.xSpeed*t, 
                bb1x2 + move1.xSpeed*t, 
                bb1y1 + move1.ySpeed*t,
                bb1y2 + move1.ySpeed*t,
                bb2x1, 
                bb2x2,
                bb2y1,
                bb2y2
            )){
                if (_bulletStorage.Has(id1) || _finishStorage.Has(id2)){ // единственные два случая, когда коллизии проходят насквозь. Да, можно спамить коллижнэвентами при любой коллизии, но это в среднем 1-2 раза в кадр, тоесть нет
                    if (!_playerStorage.Has(id2)){ // мы не хотим долбиться в пули, но умирать об пули тоже не хочется
                        const auto newEntity = world.CreateEntity();
                        _collisionStorage.Add(newEntity, {id1, id2});
                        _killMeStorage.Add(newEntity, {});
                    }
                    continue;
                }
                if (_bulletStorage.Has(id2)){ //опять же, не долбиться в пули
                    continue;
                }

                if ((nearZero(bb1x2-bb2x1) && move1.xSpeed > 0.f) || (nearZero(bb1x2-bb2x1) && move1.xSpeed < 0.f)){
                    move1.xSpeed = 0.f;
                    continue;
                } 
                if ((nearZero(bb1y2-bb2y1) && move1.ySpeed > 0.f) || (nearZero(bb1y2-bb2y1) && move1.ySpeed > 0.f)){
                    move1.ySpeed = 0.f;
                    continue;
                } 
                if (lineColliding(
                    bb1y1,
                    bb1y2,
                    bb2y1,
                    bb2y2
                )){
                    move1.xSpeed = ((bb1x1 < bb2x1)? (bb2x1-bb1x2) : (bb2x2-bb1x1)) / t;
                } else if (lineColliding(
                    bb1x1,
                    bb1x2,
                    bb2x1,
                    bb2x2
                )){
                    if (move1.ySpeed<0 && _playerStorage.Has(id1)){ // ударились головой
                        const auto newEntity = world.CreateEntity();
                        _collisionStorage.Add(newEntity, {id1, id2});
                        _killMeStorage.Add(newEntity, {});
                    }
                    move1.ySpeed = ((bb1y1 < bb2y1)? (bb2y1-bb1y2) : (bb2y2-bb1y1)) / t;
                } else {

                    float newxSpeed = ((bb1x1 < bb2x1)? (bb2x1-bb1x2) : (bb2x2-bb1x1)) / t;                
                    float newySpeed = move1.ySpeed * newxSpeed/move1.xSpeed;
                    if (!nearZero(move1.xSpeed) && lineColliding(
                        bb1y1 + newySpeed*t,
                        bb1y2 + newySpeed*t,
                        bb2y1,
                        bb2y2
                    )) {
                        move1.xSpeed = newxSpeed;
                    } else {
                        if (move1.ySpeed<0 && _playerStorage.Has(id1)){ // ударились головой
                            const auto newEntity = world.CreateEntity();
                            _collisionStorage.Add(newEntity, {id1, id2});
                            _killMeStorage.Add(newEntity, {});
                        }
                        //std::cout<<"y угол "<<bb1x1/64<<" "<<bb1x2/64<<" "<<bb1y1/64<<" "<<bb1y2/64<<" / "<<bb1x1/64+move1.xSpeed*t/64<<" "<<bb1x2/64+move1.xSpeed*t/64<<" "<<bb1y1/64+move1.ySpeed*t/64<<" "<<bb1y2/64+move1.ySpeed*t/64<<" / "<<bb1x1/64+newxSpeed*t/64<<" "<<bb1x2/64+newxSpeed*t/64<<" "<<bb1y1/64 + newySpeed*t/64<<" "<<bb1y2/64+newySpeed*t/64<<" | "<<bb2x1/64<<" "<<bb2x2/64<<" "<<bb2y1/64<<" "<<bb2y2/64<<" \n";
                        move1.ySpeed = ((bb1y1 < bb2y1)? (bb2y1-bb1y2) : (bb2y2-bb1y1)) / t;
                    }   
                }             
            }
        }
    }
}