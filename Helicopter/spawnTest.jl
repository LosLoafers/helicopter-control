

#xchannel=Channel(32)
#uchannel=Channel(32)
#put!(xchannel,x_remote)
#put!(uchannel,u_remote)

global x_remote=0
global u_remote=0
global we_should_run=true

  Su=ReentrantLock()
  Sx=ReentrantLock()

kalman=@spawn begin
  x=0
global u_remote=0
global x_remote=0
global we_should_run
  while we_should_run
    x=x+1

    lock(Su)

      u=u_remote

    unlock(Su)

    lock(Sx)

    x_remote=x;
    unlock(Sx)

    println("on kalman ",u)
    sleep(0.1)
  end

end


MPC=@spawn begin
  u=0
  global u_remote=0
  global x_remote=0
  global we_should_run
  while we_should_run
    u=u+1
    lock(Sx)

      x_hat=x_remote;

    unlock(Sx)
    lock(Su)
    u_remote=u
    unlock(Su)

    println("on MPC ",x_hat)

    sleep(0.2)
  end
end
